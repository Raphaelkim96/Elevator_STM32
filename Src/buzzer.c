#include "buzzer.h"

void buzzerInit(void)
{
    // PWM 시작 전에 타이머가 초기화되어 있는지 확인
    if (HAL_TIM_PWM_GetState(&htim4) == HAL_TIM_STATE_RESET)
    {
        MX_TIM4_Init();
    }
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

void playNote(uint16_t note, uint16_t duration)
{
    TIM4->PSC = note;
    TIM4->CCR1 = 500;  // 듀티비 50%
    HAL_Delay(duration);
    TIM4->CCR1 = 0;    // 소리 끄기
}

void stopBuzzer(void)
{
    TIM4->CCR1 = 0;
}
