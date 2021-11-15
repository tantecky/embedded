#include <zephyr.h>
#include "Arduino.h"
#include "maxik.h"
#include "MAX31856.h"

static constexpr int SDI = 13;
static constexpr int SDO = 15;
static constexpr int CS = 17;
static constexpr int SCK = 20;

static constexpr int CR0_INIT = (CR0_ONE_SHOT + CR0_OPEN_CIRCUIT_FAULT_TYPE_K
    + CR0_NOISE_FILTER_50HZ + CR0_FAULT_CLEAR + CR0_FAULT_INTERRUPT_MODE);
static constexpr int CR1_16X
    = (CR1_AVERAGE_16_SAMPLES + CR1_THERMOCOUPLE_TYPE_K);
static constexpr int CR1_1X = (CR1_AVERAGE_1_SAMPLES + CR1_THERMOCOUPLE_TYPE_K);
static constexpr int MASK_INIT
    = (~(MASK_VOLTAGE_UNDER_OVER_FAULT + MASK_THERMOCOUPLE_OPEN_FAULT));

static MAX31856 sensor_;

void maxik_init()
{
    sensor_.init(SDI, SDO, CS, SCK);
    sensor_.writeRegister(REGISTER_MASK, MASK_INIT);
    sensor_.writeRegister(REGISTER_CR1, CR1_16X);
}

float maxik_read_temp()
{
    sensor_.writeRegister(REGISTER_CR0, CR0_INIT);
    k_sleep(K_MSEC(1000));
    float t = sensor_.readThermocouple(CELSIUS);

    return t;
}
