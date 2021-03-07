#include <zephyr.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

#include "Arduino.h"

static struct device *port0 = NULL;

void pinMode(uint8_t pin, uint32_t mode)
{
    if (!port0)
    {
        port0 = (struct device *)device_get_binding("GPIO_0");
    }

    if (!port0)
    {
        printk("device_get_binding failed");
        return;
    }

    int err = gpio_pin_configure(port0, pin,
                                 mode);

    if (err)
    {
        printk("gpio_pin_configure failed %d\n", err);
        return;
    }
}

void digitalWrite(uint8_t pin, uint32_t val)
{
    int err = gpio_pin_set_raw(port0, pin, val);

    if (err)
    {
        printk("gpio_pin_set_raw failed %d\n", err);
        return;
    }
}

int digitalRead(uint8_t pin)
{
    return 0;
}