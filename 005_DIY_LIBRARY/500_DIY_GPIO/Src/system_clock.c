#include "system_clock.h"
#include "stm32f4xx.h"  
#include <stdint.h>
#include <stdio.h>


void SystemClock_Config(void) {
    // 1. Activar HSI si no está activado (por defecto sí lo está)
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    // 2. Seleccionar HSI como fuente del sistema
    RCC->CFGR &= ~RCC_CFGR_SW;            // Limpia bits SW
    RCC->CFGR |= RCC_CFGR_SW_HSI;         // Setea SW = HSI

    // 3. Esperar a que HSI esté en uso
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

    // 4. Apagar el PLL y el HSE si estaban habilitados (opcional para limpieza)
    RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_HSEON);
}