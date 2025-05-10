# Using TIM6 as the SysTick Timebase on STM32F4

This guide explains how to configure the TIM6 peripheral to replace the default SysTick timer as the timebase for HAL delays (e.g., `HAL_Delay()`), on an STM32F4 microcontroller (e.g., STM32F446RE).

## Steps

### 1. Comment Out `HAL_IncTick()` in the `SysTick_Handler`

Open the file `Src/stm32f4xx_it.c` and locate the `SysTick_Handler`. Then, comment out the call to `HAL_IncTick()`:

```c
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  // HAL_IncTick();  // Disable default tick increment
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}
```

### 2. Copy and Rename the Timebase Template

Copy the file:

```
Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_timebase_tim_template.c
```

Paste it into your project source folder and rename it:

```
Src/stm32f4xx_hal_timebase_tim.c
```

This file provides the implementation to configure TIM6 as the timebase.

### 3. Add the Timebase Source File to Your Makefile

Edit your `Makefile` to include the newly added file:

```make
SRCS = \
    Src/main.c \
    Src/usart.c \
    Src/syscalls.c \
    Src/stm32f4xx_it.c \
    Src/stm32f4xx_hal_timebase_tim.c \
    Drivers/CMSIS/Device/Source/system_stm32f4xx.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_cortex.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim_ex.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_dma.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc_ex.c \
    Drivers/stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c
```

### 4. Add the TIM6 IRQ Handler to the Startup File

Edit your `startup.s` file (or equivalent) to include the interrupt handler for TIM6. Ensure the vector table includes this entry in the correct position (IRQ #54 for TIM6\_DAC):

```asm
.section .isr_vector,"a",%progbits
    .word _estack                /* Initial stack pointer */
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .word BusFault_Handler
    .word UsageFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word DebugMon_Handler
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler

    /* External interrupts */
    .fill (70 - 16), 4, 0       /* Fill from IRQ 16 to 53 with 0s */
    .word TIM6_DAC_IRQHandler   /* IRQ 54 */
    .fill (114 - 71), 4, 0      /* Fill remaining vector table */
```

> 🛠️ Make sure you have a valid `TIM6_DAC_IRQHandler` implementation in your code or it will default to the `Default_Handler`.

---

With these steps, TIM6 will now be used by the HAL as the timebase instead of SysTick. You can verify this by observing that `HAL_Delay()` still works even when `SysTick_Handler` is disabled.
