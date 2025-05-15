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

/*
* DIY_GPIO_WritePin - Función personalizada para escribir el estado de un pin GPIO en STM32F446RE
* 
* Esta función permite establecer el estado lógico (alto o bajo) de un pin específico de un puerto GPIO,
* utilizando directamente los registros del microcontrolador a través de CMSIS.
*
* PARÁMETROS:
* - GPIO_TypeDef *GPIOx: Puntero al puerto GPIO donde se encuentra el pin (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Número de pin a modificar (puede ser una máscara, ej. GPIO_PIN_0)
* - uint8_t PinState: Estado a escribir en el pin (GPIO_PIN_SET o GPIO_PIN_RESET)
*/
void DIY_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t PinState){
    if (PinState == GPIO_PIN_SET)
    {
        GPIOx->BSRR = GPIO_Pin; // Set pin
    }
    else
    {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U; // Reset pin
    }
}

/*
* DIY_GPIO_ReadPin - Función personalizada para leer el estado de un pin GPIO en STM32F446RE
* 
* Esta función permite leer el estado lógico (alto o bajo) de un pin específico de un puerto GPIO,
* utilizando directamente los registros del microcontrolador a través de CMSIS.
*
* PARÁMETROS:
* - GPIO_TypeDef *GPIOx: Puntero al puerto GPIO a leer (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Número de pin a leer (puede ser una máscara, ej. GPIO_PIN_0)
*
* RETORNO:
* - uint8_t: GPIO_PIN_SET si el pin está en alto, GPIO_PIN_RESET si está en bajo
*/
uint8_t DIY_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    uint8_t bitstatus = (uint8_t)(GPIOx->IDR & GPIO_Pin); // Read pin
    if (bitstatus != 0)
    {
        return GPIO_PIN_SET; // Pin is set
    }
    else
    {
        return GPIO_PIN_RESET; // Pin is reset
    }
}

/*
* DIY_GPIO_TogglePin - Función personalizada para alternar el estado de un pin GPIO en STM32F446RE
* 
* Esta función permite invertir el estado lógico (alto o bajo) de un pin específico de un puerto GPIO,
* utilizando directamente los registros del microcontrolador a través de CMSIS.
*
* PARÁMETROS:
* - GPIO_TypeDef *GPIOx: Puntero al puerto GPIO donde se encuentra el pin (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Número de pin a alternar (puede ser una máscara, ej. GPIO_PIN_0)
*/
void DIY_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    GPIOx->ODR ^= GPIO_Pin; // Toggle pin       
}