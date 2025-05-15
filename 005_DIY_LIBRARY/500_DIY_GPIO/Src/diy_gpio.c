#include "stm32f4xx.h"
#include "diy_gpio.h"
#include <stdint.h>
#include <stdio.h>

/*
* DIY_GPIO_Init - Custom function to configure GPIO pins on STM32F446RE
* 
* This function allows configuring one or more pins of a specific GPIO port
* by directly accessing the microcontroller's registers via CMSIS.
*
* PARAMETERS:
* - GPIO_TypeDef *GPIOx: Pointer to the GPIO port to configure (GPIOA, GPIOB, etc.)
* - GPIO_InitTypeDef *GPIO_Init: Structure with the desired configuration for the pins
*/
void DIY_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t position;

    // Iterate through all possible port bits (0 to 15)
    for (position = 0; position < 16; position++)
    {
        // If the corresponding bit for the pin is set in GPIO_Init->Pin
        if ((GPIO_Init->Pin) & (1U << position))
        {
            //-----------------------
            // 1. CONFIGURE MODE
            //-----------------------
            // Each pin uses 2 bits in MODER, so shift by 2 * position
            GPIOx->MODER &= ~(0x3U << (position * 2)); // Clear the 2 bits
            GPIOx->MODER |= ((GPIO_Init->Mode & 0x3U) << (position * 2)); // Write new mode

            //-----------------------
            // 2. CONFIGURE OUTPUT TYPE (Push-pull or Open-drain)
            //-----------------------
            // Only applies if the pin is output or alternate function
            if ((GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || 
                (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD))
            {
                // 0: Push-pull, 1: Open-drain
                GPIOx->OTYPER &= ~(1U << position); // Clear
                GPIOx->OTYPER |= (((GPIO_Init->Mode >> 4) & 0x1U) << position); // Write type
                // The shift >> 4 extracts the bit that differentiates PP from OD
            }

            //-----------------------
            // 3. CONFIGURE SPEED
            //-----------------------
            GPIOx->OSPEEDR &= ~(0x3U << (position * 2)); // Clear
            GPIOx->OSPEEDR |= ((GPIO_Init->Speed & 0x3U) << (position * 2)); // Write speed

            //-----------------------
            // 4. CONFIGURE PULL-UP / PULL-DOWN
            //-----------------------
            GPIOx->PUPDR &= ~(0x3U << (position * 2)); // Clear
            GPIOx->PUPDR |= ((GPIO_Init->Pull & 0x3U) << (position * 2)); // Write pull
        }
    }
}

/*
* DIY_GPIO_WritePin - Custom function to write the state of a GPIO pin on STM32F446RE
* 
* This function sets the logical state (high or low) of a specific pin of a GPIO port,
* by directly accessing the microcontroller's registers via CMSIS.
*
* PARAMETERS:
* - GPIO_TypeDef *GPIOx: Pointer to the GPIO port where the pin is located (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Pin number to modify (can be a mask, e.g. GPIO_PIN_0)
* - uint8_t PinState: State to write to the pin (GPIO_PIN_SET or GPIO_PIN_RESET)
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
* DIY_GPIO_ReadPin - Custom function to read the state of a GPIO pin on STM32F446RE
* 
* This function reads the logical state (high or low) of a specific pin of a GPIO port,
* by directly accessing the microcontroller's registers via CMSIS.
*
* PARAMETERS:
* - GPIO_TypeDef *GPIOx: Pointer to the GPIO port to read (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Pin number to read (can be a mask, e.g. GPIO_PIN_0)
*
* RETURN:
* - uint8_t: GPIO_PIN_SET if the pin is high, GPIO_PIN_RESET if the pin is low
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
* DIY_GPIO_TogglePin - Custom function to toggle the state of a GPIO pin on STM32F446RE
* 
* This function inverts the logical state (high or low) of a specific pin of a GPIO port,
* by directly accessing the microcontroller's registers via CMSIS.
*
* PARAMETERS:
* - GPIO_TypeDef *GPIOx: Pointer to the GPIO port where the pin is located (GPIOA, GPIOB, etc.)
* - uint16_t GPIO_Pin: Pin number to toggle (can be a mask, e.g. GPIO_PIN_0)
*/
void DIY_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    GPIOx->ODR ^= GPIO_Pin; // Toggle pin       
}