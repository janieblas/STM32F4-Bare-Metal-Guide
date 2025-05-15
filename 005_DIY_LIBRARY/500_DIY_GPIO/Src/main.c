#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "diy_gpio.h"

#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U)
#define GPIOA_BASE (AHB1_BASE + 0x0U)
#define RCC_BASE (AHB1_BASE + 0x3800U)

#define RCC_AHB1ENR_OFFSET (0x30U)
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET))
#define RCC_AHB1ENR_GPIOAEN (0x00U)

void main(void)
{
  // Enable clock for GPIOA
  *RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN);

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_5;             // Pin 5
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Output push-pull
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // Medium speed
  GPIO_InitStruct.Pull = GPIO_NOPULL;           // No pull-up or pull-down
  
  DIY_GPIO_Init(GPIOA, &GPIO_InitStruct);       // Configure pin PA5

  while(1){
    DIY_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Turn LED on
    for (volatile int i = 0; i < 1000000; i++); // Wait
    DIY_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Turn LED off
    for (volatile int i = 0; i < 1000000; i++); // Wait
  }
}
