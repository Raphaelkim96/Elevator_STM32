/*
 * led.c
 *
 *  Created on: Jan 15, 2025
 *      Author: user
 */

#include "led.h"

/*
 * PC1 pin : Red,
 * PC2 pin : Green
 * PC3 pin : Blue
 */

void Red_LED_On(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void Red_LED_Off(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}

void Green_LED_On(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

void Green_LED_Off(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
}

void Blue_LED_On(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
}

void Blue_LED_Off(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
}

// 모든 LED 끄기
void All_LED_Off(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
}
