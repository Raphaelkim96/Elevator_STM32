/*
 * button.c
 *
 *  Created on: Jan 15, 2025
 *      Author: gyromind
 */


/*
 * button.c
 *
 *  Created on: Jan 7, 2025
 *      Author: gyromind
 */


#include "button.h"


BUTTON_TBL btn_tbl[3]=
    {
        {GPIOC, GPIO_PIN_8, 1},
        {GPIOC, GPIO_PIN_6, 1},
        {GPIOC, GPIO_PIN_5, 1},
    };



bool buttonInit()
{
  bool ret = true;

  return ret;

}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;

  if(HAL_GPIO_ReadPin(btn_tbl[ch].port, btn_tbl[ch].pinNumber) == btn_tbl[ch].onState)
  {
    HAL_Delay(30);
    if(HAL_GPIO_ReadPin(btn_tbl[ch].port, btn_tbl[ch].pinNumber) == btn_tbl[ch].onState)
    {
      ret = true;
    }
  }

  return ret;
}
