#include "Arduino.h"
#include "maxik.h"
#include "MAX31856.h"

static constexpr int SDI = 13;
static constexpr int SDO = 15;
static constexpr int CS = 17;
static constexpr int SCK = 20;

static MAX31856 sensor;

void maxik_init()
{
    sensor.init(SDI, SDO, CS, SCK);
}
