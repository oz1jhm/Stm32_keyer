/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define NOTINUSE13_Pin GPIO_PIN_14
#define NOTINUSE13_GPIO_Port GPIOC
#define DIH_paddle_Pin GPIO_PIN_15
#define DIH_paddle_GPIO_Port GPIOC
#define NOTINUSE12_Pin GPIO_PIN_2
#define NOTINUSE12_GPIO_Port GPIOA
#define NOTINUSE11_Pin GPIO_PIN_3
#define NOTINUSE11_GPIO_Port GPIOA
#define NOTINUSE10_Pin GPIO_PIN_4
#define NOTINUSE10_GPIO_Port GPIOA
#define NOTINUSE8_Pin GPIO_PIN_5
#define NOTINUSE8_GPIO_Port GPIOA
#define NOTINUSE9_Pin GPIO_PIN_6
#define NOTINUSE9_GPIO_Port GPIOA
#define NOTINUSE7_Pin GPIO_PIN_7
#define NOTINUSE7_GPIO_Port GPIOA
#define NOTINUSE6_Pin GPIO_PIN_0
#define NOTINUSE6_GPIO_Port GPIOB
#define NOTINUSE5_Pin GPIO_PIN_1
#define NOTINUSE5_GPIO_Port GPIOB
#define NOTINUSE4_Pin GPIO_PIN_2
#define NOTINUSE4_GPIO_Port GPIOB
#define TX3_Pin GPIO_PIN_12
#define TX3_GPIO_Port GPIOB
#define TX2_Pin GPIO_PIN_13
#define TX2_GPIO_Port GPIOB
#define TX1_Pin GPIO_PIN_14
#define TX1_GPIO_Port GPIOB
#define DAH_paddle1_Pin GPIO_PIN_15
#define DAH_paddle1_GPIO_Port GPIOB
#define DIH_paddle1_Pin GPIO_PIN_8
#define DIH_paddle1_GPIO_Port GPIOA
#define DAH_paddle2_Pin GPIO_PIN_9
#define DAH_paddle2_GPIO_Port GPIOA
#define DIH_paddle2_Pin GPIO_PIN_10
#define DIH_paddle2_GPIO_Port GPIOA
#define NOTINUSE2_Pin GPIO_PIN_11
#define NOTINUSE2_GPIO_Port GPIOA
#define NOTINUSE1_Pin GPIO_PIN_12
#define NOTINUSE1_GPIO_Port GPIOA
#define Rotary_switch_Pin GPIO_PIN_15
#define Rotary_switch_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_3
#define LED_RED_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_4
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_5
#define LED_BLUE_GPIO_Port GPIOB
#define NOTINUSE14_Pin GPIO_PIN_8
#define NOTINUSE14_GPIO_Port GPIOB
#define DAH_paddle_Pin GPIO_PIN_9
#define DAH_paddle_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
unsigned char char_ringbuffer[64];
unsigned char ptr_Get_ringbuffer;
unsigned char ptr_Send_ringbuffer;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
