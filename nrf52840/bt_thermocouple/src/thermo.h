#ifndef BEEC138E_ECB0_424C_A0A7_9A4A4982DF57
#define BEEC138E_ECB0_424C_A0A7_9A4A4982DF57

#ifdef __cplusplus
extern "C"
{
#endif

    ssize_t read_temperature(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr, void *buf,
                             uint16_t len, uint16_t offset);

    void ccc_cfg_changed(const struct bt_gatt_attr *attr,
                         uint16_t value);

    void update_temperature();

    bool check_temperature();

#ifdef __cplusplus
}
#endif

#endif /* BEEC138E_ECB0_424C_A0A7_9A4A4982DF57 */