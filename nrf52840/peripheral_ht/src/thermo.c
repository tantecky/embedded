#include <sys/byteorder.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>
#include <bluetooth/uuid.h>
#include <sys/printk.h>

#include "thermo.h"
#include "maxik.h"

static float temperature = (0.0F / 0.0F);
static uint8_t payload[5] = {0};
static bool notif_enabled = false;

BT_GATT_SERVICE_DEFINE(thermo_svc,
                       BT_GATT_PRIMARY_SERVICE(BT_UUID_ESS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_TEMPERATURE,
                                              BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                                              BT_GATT_PERM_READ, read_temperature, NULL,
                                              &temperature),
                       BT_GATT_CCC(ccc_cfg_changed,
                                   BT_GATT_PERM_READ | BT_GATT_PERM_WRITE), );

ssize_t read_temperature(struct bt_conn *conn,
                         const struct bt_gatt_attr *attr, void *buf,
                         uint16_t len, uint16_t offset)
{
    printk("Reading temp %f\n", temperature);

    return bt_gatt_attr_read(conn, attr, buf, len, offset, &temperature,
                             sizeof(temperature));
}

void ccc_cfg_changed(const struct bt_gatt_attr *attr,
                     uint16_t value)
{
    ARG_UNUSED(attr);

    notif_enabled = (value == BT_GATT_CCC_NOTIFY);

    printk("Temperature Notifications %s\n", notif_enabled ? "enabled" : "disabled");
}

void update_temperature()
{
    // blocking, takes 1 sec
    temperature = maxik_read_temp();
    printk("Updating temp %f\n", temperature);
}

bool check_temperature()
{
    if (!notif_enabled)
    {
        return false;
    }

    update_temperature();

    uint32_t mantissa = (uint32_t)(temperature * 100);
    uint8_t exponent = (uint8_t)-2;

    payload[0] = 0; /* temperature in celcius */
    sys_put_le24(mantissa, (uint8_t *)&payload[1]);
    payload[4] = exponent;

    bt_gatt_notify(NULL, &thermo_svc.attrs[1], &payload, sizeof(payload));

    return true;
}