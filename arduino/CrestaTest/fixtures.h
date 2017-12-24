#ifndef FIXTURES_H_KNFTXVH7
#define FIXTURES_H_KNFTXVH7

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;
#define CHANGE 1

unsigned long micros();
void attachInterrupt(uint8_t, void (*)(void), int mode);

#endif /* end of include guard: FIXTURES_H_KNFTXVH7 */

