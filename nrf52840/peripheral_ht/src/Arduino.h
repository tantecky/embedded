#ifndef DA2E9751_365B_4134_8D8F_A48EA6856F43
#define DA2E9751_365B_4134_8D8F_A48EA6856F43

#include <stdint.h>
#include <zephyr.h>

typedef uint8_t byte;

#define LOW (0x0)
#define HIGH (0x1)
#define INPUT (0x0)
#define OUTPUT (0x1)
#define INPUT_PULLUP (0x2)

#define delayMicroseconds(x) NRFX_DELAY_US((x))

void pinMode(uint32_t ulPin, uint32_t ulMode);
void digitalWrite(uint32_t ulPin, uint32_t ulVal);
int digitalRead(uint32_t ulPin);

#endif /* DA2E9751_365B_4134_8D8F_A48EA6856F43 */
