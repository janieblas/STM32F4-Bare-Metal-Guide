#include "diy_clock.h"
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>

// Configures the oscillator (HSE, HSI, PLL) according to the parameters in RCC_OscInitStruct
DIY_StatusTypeDef DIY_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct){
    // Configure HSE (High Speed External oscillator)
    if (RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_HSE) {
        if (RCC_OscInitStruct->HSEState == RCC_HSE_ON) {
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY)); // Wait until HSE is ready
        } else if (RCC_OscInitStruct->HSEState == RCC_HSE_OFF) {
            RCC->CR &= ~RCC_CR_HSEON;
        }
    }

    // Configure HSI (High Speed Internal oscillator)
    if (RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_HSI) {
        if (RCC_OscInitStruct->HSIState == RCC_HSI_ON) {
            RCC->CR |= RCC_CR_HSION;
            while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready
        } else if (RCC_OscInitStruct->HSIState == RCC_HSI_OFF) {
            RCC->CR &= ~RCC_CR_HSION;
        }
    }

    // Configure PLL (Phase Locked Loop)
    if (RCC_OscInitStruct->PLL.PLLState == RCC_PLL_ON) {
        // Turn off PLL if it was already on
        if (RCC->CR & RCC_CR_PLLON) {
            RCC->CR &= ~RCC_CR_PLLON;
            while (RCC->CR & RCC_CR_PLLRDY); // Wait until PLL is off
        }

        // Set PLL configuration
        RCC->PLLCFGR = (RCC_OscInitStruct->PLL.PLLSource |
                        (RCC_OscInitStruct->PLL.PLLM << RCC_PLLCFGR_PLLM_Pos) |
                        (RCC_OscInitStruct->PLL.PLLN << RCC_PLLCFGR_PLLN_Pos) |
                        (((RCC_OscInitStruct->PLL.PLLP >> 1) - 1) << RCC_PLLCFGR_PLLP_Pos) |
                        (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos));

        RCC->CR |= RCC_CR_PLLON;
        while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait until PLL is ready
    }

    return DIY_OK;
}

// Configures the system clock, bus prescalers, and flash latency
DIY_StatusTypeDef DIY_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency){
    // Configure Flash Latency
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLatency;

    // Configure prescalers (AHB, APB1, APB2 dividers)
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= (RCC_ClkInitStruct->AHBCLKDivider |
                  RCC_ClkInitStruct->APB1CLKDivider |
                  RCC_ClkInitStruct->APB2CLKDivider);

    // Change SYSCLK source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_ClkInitStruct->SYSCLKSource;

    // Wait until the new SYSCLK source is used
    while ((RCC->CFGR & RCC_CFGR_SWS) != (RCC_ClkInitStruct->SYSCLKSource << 2));

    return DIY_OK;
}

// Stub for MCO (Microcontroller Clock Output) configuration
void DIY_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv){}

// Stub to enable Clock Security System
void DIY_RCC_EnableCSS(void){}

// Stub to disable Clock Security System
void DIY_RCC_DisableCSS(void){}
