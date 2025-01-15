/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stepper.h"
#include "button.h"
#include "I2C_LCD.h"
#include "led.h"
#include "buzzer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define STATE_IDLE    0
#define STATE_FLOOR1  1
#define STATE_FLOOR2  2
#define STATE_FLOOR3  3
#define STATE_UP      4
#define STATE_DOWN    5
#define STATE_ARRIVED 6

#define PHOTO_1     GPIO_PIN_2
#define PHOTO_2     GPIO_PIN_10
#define PHOTO_3     GPIO_PIN_11



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile int current_floor = 1;  // 현재 층
volatile int target_floor = 1;   // 목표 층
volatile int is_moving = 0;      // 이동 중 여부
uint8_t flag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == PHOTO_1)
  {
      current_floor = 1;

      if (target_floor == 1) {
          is_moving = 0;


          stepMotor(8); // 모터정지
          //playNote(Do, 200);



      }
  }
  else if (GPIO_Pin == PHOTO_2)
  {
      current_floor = 2;

      if (target_floor == 2) {
          is_moving = 0;
          //2층 도착 lcd




          stepMotor(8); // 모터정지
          //playNote(Do, 200);


      }
  }
  else if (GPIO_Pin == PHOTO_3)
  {
      current_floor = 3;

      if (target_floor == 3) {
          is_moving = 0;
          //3층 도착 lcd


          stepMotor(8);
          //playNote(Do, 200);


      }
  }

}


void moveElevator(void)
{
  if (current_floor == target_floor)
  {
    is_moving = 0;
//    stepMotor(8);
//    playNote(Si, 200);


    return;
  }

  is_moving = 1;
  flag =0;
  playNote(Si, 200);
  All_LED_Off();
  Red_LED_On();
  uint8_t direction = (target_floor > current_floor) ? DIR_CW : DIR_CCW;

  //올라가는 lcd
  if(direction == DIR_CW)
  {
    moveCursor(1, 0);
    lcdString("Going Up           ");
  }
  else if(direction == DIR_CCW)
  {
    moveCursor(1, 0);
    lcdString("Going Down         ");
  }

  //목표층에 도달할 때까지 스텝모터 구동

  while(is_moving){
    rotateDegree(1, direction);
  }


}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM11_Init();
  MX_I2C1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  buzzerInit();
  buttonInit();
  lcdInit();

  HAL_Delay(200);

  //초기화 층수
  moveCursor(0, 0);
  lcdString("1st Floor           ");
  moveCursor(1, 0);
  lcdString("Welcome!!           ");





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


     //버튼 입력 확인
    if (!is_moving)  // 엘리베이터가 멈춰있을 때만 버튼 입력 처리
    {
      //버튼 LCD
      switch (current_floor) {
        case 1:
          if(!flag){
          moveCursor(0, 0);
          lcdString("1st Floor           ");
          moveCursor(1, 0);
          lcdString("Door Open           ");
          HAL_Delay(1000);
          flag =1;
          }
          else{
          moveCursor(0, 0);
          lcdString("1st Floor           ");
          moveCursor(1, 0);
          lcdString("Door Close           ");
          HAL_Delay(1000);
          }

          break;
        case 2:
          if(!flag){
          moveCursor(0, 0);
          lcdString("2nd Floor           ");
          moveCursor(1, 0);
          lcdString("Door Open           ");
          HAL_Delay(1000);
          flag =1;
          }
          else{
          moveCursor(0, 0);
          lcdString("2nd Floor           ");
          moveCursor(1, 0);
          lcdString("Door Close           ");
          HAL_Delay(1000);
          }
          break;
        case 3:
          if(!flag){
          moveCursor(0, 0);
          lcdString("3rd Floor           ");
          moveCursor(1, 0);
          lcdString("Door Open           ");
          HAL_Delay(1000);
          flag=1;
          }
          else{
          moveCursor(0, 0);
          lcdString("3rd Floor           ");
          moveCursor(1, 0);
          lcdString("Door Close           ");
          HAL_Delay(1000);
          }
          break;
        default:

          break;
      }

      All_LED_Off();
      Green_LED_On();


      if (buttonGetPressed(0))
      {
        target_floor = 1;
        moveElevator();
        //rotateDegree(450, 1);
      }
      else if (buttonGetPressed(1))
      {
        target_floor = 2;
        moveElevator();
        //rotateDegree(450, 1);
      }
      else if (buttonGetPressed(2))
      {
        target_floor = 3;
        moveElevator();
        //rotateDegree(450, 1);
      }
    }

    HAL_Delay(100);  // 디바운싱




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
