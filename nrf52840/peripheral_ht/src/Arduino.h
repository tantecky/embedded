#ifndef DA2E9751_365B_4134_8D8F_A48EA6856F43
#define DA2E9751_365B_4134_8D8F_A48EA6856F43

#include <stdint.h>
#include <zephyr.h>
#include <drivers/gpio.h>

typedef uint8_t byte;

#define LOW (0x0)
#define HIGH (0x1)
#define INPUT (GPIO_INPUT)
#define OUTPUT (GPIO_OUTPUT)
#define INPUT_PULLUP (GPIO_INPUT | GPIO_PULL_UP)

#define delayMicroseconds(x) NRFX_DELAY_US((x))

void pinMode(uint8_t pin, uint32_t mode);
void digitalWrite(uint8_t pin, uint32_t val);
int digitalRead(uint8_t pin);

#endif /* DA2E9751_365B_4134_8D8F_A48EA6856F43 */
