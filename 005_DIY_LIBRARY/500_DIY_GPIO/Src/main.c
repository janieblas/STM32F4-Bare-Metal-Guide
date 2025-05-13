#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_clock.h"
#include "diy_gpio.h"

#define LED_PIN 5



void main(void)
{
  // Habilitar el reloj para GPIOA
  SystemClock_Config();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_5;             // Pin 5
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Salida push-pull
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // Velocidad media
  GPIO_InitStruct.Pull = GPIO_NOPULL;           // Sin resistencias
  
  DIY_GPIO_Init(GPIOA, &GPIO_InitStruct);       // Configurar el pin PA5


  while(1){

  }
}
