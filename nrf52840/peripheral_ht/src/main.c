/* main.c - Application main entry point */

/*
 * Copyright (c) 2019 Aaron Tsui <aaron.tsui@outlook.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>

#include <dk_buttons_and_leds.h>

#include "hts.h"

#define LED_GREEN (2)
#define LED_RED (1)
#define LED_BLUE (3)

struct bt_conn *default_conn;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
				  BT_UUID_16_ENCODE(BT_UUID_HTS_VAL),
				  BT_UUID_16_ENCODE(BT_UUID_DIS_VAL),
				  BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err)
	{
		printk("Connection failed (err 0x%02x)\n", err);
	}
	else
	{
		default_conn = bt_conn_ref(conn);
		printk("Connected\n");

		dk_set_led_on(LED_RED);
		dk_set_led_off(LED_GREEN);
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);

	if (default_conn)
	{
		bt_conn_unref(default_conn);
		default_conn = NULL;
	}

	dk_set_led_on(LED_GREEN);
	dk_set_led_off(LED_RED);
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	hts_init();

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err)
	{
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

static struct bt_conn_auth_cb auth_cb_display = {
	.cancel = auth_cancel,
};

static void bas_notify(void)
{
	uint8_t battery_level = bt_bas_get_battery_level();

	battery_level--;

	if (!battery_level)
	{
		battery_level = 100U;
	}

	bt_bas_set_battery_level(battery_level);
}

void main(void)
{

	dk_leds_init();

	int err;

	err = bt_enable(NULL);
	if (err)
	{
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_conn_cb_register(&conn_callbacks);
	bt_conn_auth_cb_register(&auth_cb_display);

	/* Implement indicate. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */

	dk_set_led_on(LED_GREEN);
	dk_set_led_off(LED_RED);

	while (1)
	{
		k_sleep(K_SECONDS(1));

		if (default_conn)
		{
			/* Temperature measurements simulation */
			hts_indicate();

			/* Battery level simulation */
			bas_notify();

			dk_set_led_on(LED_BLUE);
			k_sleep(K_MSEC(100));
			dk_set_led_off(LED_BLUE);
		}
	}
}
