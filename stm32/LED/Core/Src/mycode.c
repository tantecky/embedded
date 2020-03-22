/*
 * mycode.c
 *
 *  Created on: Mar 22, 2020
 *      Author: tom
 */
#include "stm32f1xx_hal.h"

void blink(void) {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	HAL_Delay(50);
}

void setup(void) {
	// led on
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	// led off
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

}

void loop(void) {
	blink();
}

