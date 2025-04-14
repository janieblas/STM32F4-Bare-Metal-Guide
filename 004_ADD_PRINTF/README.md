# Implementing printf in STM32F446RE

This document explains how to implement printf functionality in your STM32F446RE project.

## Required Files

1. `syscalls.c` - Implements the system calls needed for printf
2. `usart.c` and `usart.h` - Handles USART communication
3. Modified linker script with standard library support
4. Modified Makefile with standard library flags

## Required Tools

1. Serial Monitor Extension - To view the UART output:
   - For VS Code: Install "Serial Monitor" extension
   - Alternative tools: PuTTY, Tera Term, or any other serial terminal
   - Configure the serial monitor with:
     - Baud rate: 115200
     - Port: COM port where your STM32 is connected
     - Data bits: 8
     - Stop bits: 1
     - Parity: None

## Implementation Steps

### 1. USART Configuration

First, configure USART in your `usart.c`:

```c
void usart_init(USART_TypeDef *USARTx, uint32_t baudrate) {
    // Enable USART clock
    if (USARTx == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
    
    // Configure GPIO for USART
    // PA2 - TX, PA3 - RX
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (2 << 4) | (2 << 6);  // Alternate function mode
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12); // AF7 for USART2
    
    // Configure USART
    USARTx->BRR = SystemCoreClock / baudrate;
    USARTx->CR1 = USART_CR1_TE | USART_CR1_UE; // Enable transmitter and USART
}
```

### 2. System Calls Implementation

In `syscalls.c`, implement the necessary system calls:

```c
#include <sys/stat.h>
#include <sys/times.h>
#include "usart.h"
#include <errno.h>

// Implement _write for printf
int _write(int file, char *ptr, int len) {
    (void) file;
    for (uint32_t i = 0; i < len; i++) {
        usart_write(USART2, *ptr++);
    }
    return len;
}

// Other required system calls...
```

### 3. Makefile Configuration

Add these flags to your Makefile:

```makefile
CFLAGS = -mcpu=cortex-m4 -mthumb -g -O0 -Wl,--no-warn-rwx-segments
LDFLAGS = -T Linker_script/linker_script.ld -specs=nosys.specs -specs=nano.specs
```

### 4. Linker Script Modifications

Add these symbols to your linker script:

```ld
.bss : 
{ 
    . = ALIGN(4); 
    _sbss = .; 
    __bss_start__ = .;
    *(.bss) 
    . = ALIGN(4); 
    _ebss = .; 
    __bss_end__ = .;
} >SRAM 
```


## Important Notes

1. Make sure to initialize USART before using printf
2. The printf output will be sent through USART2 by default
3. You can redirect printf to a different USART by modifying the `_write` function in `syscalls.c`
4. The standard library implementation uses the nano version for smaller code size
5. Heap management is handled by the `_sbrk` function in `syscalls.c`

## Troubleshooting

1. If printf doesn't work:
   - Check USART initialization
   - Verify baud rate settings
   - Ensure USART pins are correctly configured
   - Check if the linker script has the required symbols

2. If you get linker errors:
   - Verify the Makefile flags
   - Check if all required files are included in the build
   - Ensure the linker script is properly configured

3. If you get memory errors:
   - Check the heap size in `_sbrk`
   - Verify the stack size in the linker script
   - Ensure proper memory allocation in the linker script

