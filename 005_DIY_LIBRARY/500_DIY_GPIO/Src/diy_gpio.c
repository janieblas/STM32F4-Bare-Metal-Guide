#include "stm32f4xx.h"
#include "diy_gpio.h"
#include <stdint.h>
#include <stdio.h>

/*
* DIY_GPIO_Init - Función personalizada para configurar pines GPIO en STM32F446RE
* 
* Esta función permite configurar uno o varios pines de un puerto GPIO específico
* utilizando directamente los registros del microcontrolador a través de CMSIS.
*
* PARÁMETROS:
* - GPIO_TypeDef *GPIOx: Puntero al puerto GPIO a configurar (GPIOA, GPIOB, etc.)
* - GPIO_InitTypeDef *GPIO_Init: Estructura con la configuración deseada para los pines
*
* REGISTROS UTILIZADOS:
* Registro    Función                                          Bits por pin
* -----------------------------------------------------------------------------
* MODER       Configura el modo del pin                        2 bits
*             00: Entrada, 01: Salida, 10: Alternate, 11: Analógico
*
* OTYPER      Configura el tipo de salida                      1 bit
*             0: Push-pull (por defecto), 1: Open-drain
*
* OSPEEDR     Configura la velocidad del pin                   2 bits
*             00: Baja, 01: Media, 10: Alta, 11: Muy alta
*
* PUPDR       Configura resistencias internas                  2 bits
*             00: Sin pull-up/down, 01: Pull-up, 10: Pull-down, 11: Reservado
*
* EJEMPLO DE USO:
* Para configurar el pin PA5 como salida push-pull, velocidad media y sin resistencias:
*
* GPIO_InitTypeDef GPIO_InitStruct = {0};
* GPIO_InitStruct.Pin = GPIO_PIN_5;             // Pin 5
* GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Salida push-pull
* GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // Velocidad media
* GPIO_InitStruct.Pull = GPIO_NOPULL;           // Sin resistencias
* DIY_GPIO_Init(GPIOA, &GPIO_InitStruct);       // Configurar el pin PA5
*/

void DIY_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t position;

    // Recorremos todos los bits posibles del puerto (0 a 15)
    for (position = 0; position < 16; position++)
    {
        // Si el bit correspondiente al pin está activado en GPIO_Init->Pin
        if ((GPIO_Init->Pin) & (1U << position))
        {
            //-----------------------
            // 1. CONFIGURAR MODO
            //-----------------------
            // Cada pin usa 2 bits en MODER, así que desplazamos 2 * posición
            GPIOx->MODER &= ~(0x3U << (position * 2)); // Limpiar los 2 bits
            GPIOx->MODER |= ((GPIO_Init->Mode & 0x3U) << (position * 2)); // Escribir nuevo modo

            //-----------------------
            // 2. CONFIGURAR TIPO DE SALIDA (Push-pull u Open-drain)
            //-----------------------
            // Solo aplica si el pin es de salida o alternate function
            if ((GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || 
                (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD))
            {
                // 0: Push-pull, 1: Open-drain
                GPIOx->OTYPER &= ~(1U << position); // Limpiar
                GPIOx->OTYPER |= (((GPIO_Init->Mode >> 4) & 0x1U) << position); // Escribir tipo
                // El desplazamiento >> 4 es para extraer el bit que diferencia PP de OD
            }

            //-----------------------
            // 3. CONFIGURAR VELOCIDAD
            //-----------------------
            GPIOx->OSPEEDR &= ~(0x3U << (position * 2)); // Limpiar
            GPIOx->OSPEEDR |= ((GPIO_Init->Speed & 0x3U) << (position * 2)); // Escribir velocidad

            //-----------------------
            // 4. CONFIGURAR PULL-UP / PULL-DOWN
            //-----------------------
            GPIOx->PUPDR &= ~(0x3U << (position * 2)); // Limpiar
            GPIOx->PUPDR |= ((GPIO_Init->Pull & 0x3U) << (position * 2)); // Escribir pull
        }
    }
}


void DIY_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t PinState){}
uint8_t DIY_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){}
void DIY_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){}