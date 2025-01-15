#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include "tim.h"

// 음계 정의
#define Do    383  // 도착음
#define Si    203  // 출발음

void buzzerInit(void);
void playNote(uint16_t note, uint16_t duration);
void stopBuzzer(void);

#endif /* INC_BUZZER_H_ */
