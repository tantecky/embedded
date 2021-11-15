#ifndef DA2E9751_365B_4134_8D8F_A48EA6856F43
#define DA2E9751_365B_4134_8D8F_A48EA6856F43

#ifdef __cplusplus
extern "C"
{
#endif

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

    void pinMode(uint32_t pin, uint32_t mode);
    void digitalWrite(uint32_t pin, uint32_t val);
    int digitalRead(uint32_t pin);

#ifdef __cplusplus
}
#endif

#endif /* DA2E9751_365B_4134_8D8F_A48EA6856F43 */
