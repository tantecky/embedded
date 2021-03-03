#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>
#include <bluetooth/uuid.h>
#include <sys/printk.h>
#include <random/rand32.h>

#include "thermo.h"

static float temperature = -1;
static bool notif_enabled = false;

BT_GATT_SERVICE_DEFINE(thermo,
                       BT_GATT_PRIMARY_SERVICE(BT_UUID_ESS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_TEMPERATURE,
                                              BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                                              BT_GATT_PERM_READ, read_temperature, NULL,
                                              &temperature),
                       BT_GATT_CCC(ccc_cfg_changed,
                                   BT_GATT_PERM_READ | BT_GATT_PERM_WRITE), );

static ssize_t read_temperature(struct bt_conn *conn,
                                const struct bt_gatt_attr *attr, void *buf,
                                uint16_t len, uint16_t offset)
{
    float val = temperature;

    return bt_gatt_attr_read(conn, attr, buf, len, offset, &val,
                             sizeof(val));
}

static void ccc_cfg_changed(const struct bt_gatt_attr *attr,
                            uint16_t value)
{
    ARG_UNUSED(attr);

    notif_enabled = (value == BT_GATT_CCC_NOTIFY);

    printk("Temperature Notifications %s", notif_enabled ? "enabled" : "disabled");
}

bool update_temperature()
{

    if (!notif_enabled)
    {
        return false;
    }

    temperature = (float)sys_rand32_get() / (float)(UINT32_MAX / 100);

    bt_gatt_notify(NULL, &thermo.attrs[1], &temperature, sizeof(temperature));

    return true;
}