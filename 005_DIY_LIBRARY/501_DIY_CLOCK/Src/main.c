#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include "diy_gpio.h"
#include "diy_clock.h"
#include "minimal_lib.h"

void SystemClock_Config(void);
void GPIOA_Init(void);

void main(void)
{

  SystemClock_Config(); // Configure system clock
  GPIOA_Init(); // Initialize GPIOA

  while(1){
    DIY_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Turn LED on
    for (volatile int i = 0; i < 200000; i++); // Wait
    DIY_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Turn LED off
    for (volatile int i = 0; i < 200000; i++); // Wait
  }
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // 1. Configurar oscilador HSI
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;   // PLL apagado

    DIY_RCC_OscConfig(&RCC_OscInitStruct);

    // 2. Seleccionar HSI como fuente de reloj del sistema
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK 
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;    // HCLK = SYSCLK (16 MHz)
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;     // APB1 a 16 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;     // APB2 a 16 MHz

    DIY_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void GPIOA_Init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE() ; // Enable clock for GPIOA

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;             // Pin 5
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Output push-pull
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // Medium speed
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // No pull-up or pull-down

    DIY_GPIO_Init(GPIOA, &GPIO_InitStruct);       // Configure pin PA5
}