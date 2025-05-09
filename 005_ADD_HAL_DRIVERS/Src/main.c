#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "usart.h"

#define LED_PIN 5

void main(void)
{

  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);
  
  // do two dummy reads after enabling the peripheral clock, as per the errata
   volatile uint32_t dummy;
   dummy = RCC->AHB1ENR;
   dummy = RCC->AHB1ENR;

  GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos);

  usart_init(USART2);

  while(1)
  {
    //printf("Hello, World!\r\n");
    GPIOA->ODR ^= (1 << LED_PIN);
    for (uint32_t i = 0; i < 600000; i++); // Simple delay
  }
}

//test2