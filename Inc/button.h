/*
 * button.h
 *
 *  Created on: Jan 7, 2025
 *      Author: gyromind
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef struct
{
  GPIO_TypeDef  *port;
  uint16_t      pinNumber;
  GPIO_PinState onState;
}BUTTON_TBL;


bool buttonInit();
bool buttonGetPressed(uint8_t ch);



#endif /* INC_BUTTON_H_ */
