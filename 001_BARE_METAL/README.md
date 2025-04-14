# Bare Metal Programming for STM32F446RE

This document explains the fundamentals of bare metal programming for STM32 microcontrollers, focusing on the STM32F446RE.

## Table of Contents
1. [Basic Concepts](#basic-concepts)
2. [Project Structure](#project-structure)
3. [Startup Script](#startup-script)
4. [Linker Script](#linker-script)
5. [Makefile](#makefile)
6. [Basic Compilation Process](#basic-compilation-process)

## Basic Concepts

### What is Bare Metal Programming?
Bare metal programming means writing code that runs directly on the hardware without an operating system. This gives you complete control over the hardware but requires you to handle everything yourself.

### Key Components
1. **Startup Code**: Initializes the microcontroller and sets up the runtime environment
2. **Linker Script**: Defines memory layout and section placement
3. **Makefile**: Automates the build process
4. **Main Application**: Your actual program code

## Project Structure

```
001_BARE_METAL/
├── main.c          # Main application code
├── startup.s       # Assembly startup code
├── linker_script.ld # Memory layout definition
└── Makefile        # Build automation
```

## Startup Script

The startup script (`startup.s`) is crucial for initializing the microcontroller. Here's what it does:

```assembly
.syntax unified
.cpu cortex-m4
.thumb

// Vector table
.section .isr_vector
.word _estack             // Stack pointer initial value
.word Reset_Handler       // Reset handler
.word NMI_Handler         // NMI handler
.word HardFault_Handler   // Hard fault handler
// ... other interrupt vectors ...

// Reset handler
.section .text
.thumb_func
Reset_Handler:
    // Initialize .data section
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    b data_copy_check
data_copy:
    ldr r3, [r2], #4
    str r3, [r0], #4
data_copy_check:
    cmp r0, r1
    blt data_copy

    // Clear .bss section
    ldr r0, =_sbss
    ldr r1, =_ebss
    mov r2, #0
    b bss_clear_check
bss_clear:
    str r2, [r0], #4
bss_clear_check:
    cmp r0, r1
    blt bss_clear

    // Call main
    bl main
    b .
```

## Linker Script

The linker script (`linker_script.ld`) defines memory layout:

```ld
ENTRY(Reset_Handler)

/* Memory definitions */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Section definitions */
SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM
}
```

## Makefile

The Makefile automates the build process:

```makefile
# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -g -O0
ASFLAGS = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T linker_script.ld -nostdlib

# Files
SRCS = main.c
ASRCS = startup.s
OBJS = $(SRCS:.c=.o) $(ASRCS:.s=.o)

# Target
TARGET = program.elf

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
    $(AS) $(ASFLAGS) $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)
```

## Basic Compilation Process

### Simple Compilation Flow

```
+---------------+     +------------------+     +--------------+     +------------------+     +------------+
|   Source      |     |    Compiler     |     |   Object     |     |     Linker      |     |   Output   |
|   Files       | --> | arm-none-eabi-  | --> |   Files      | --> | arm-none-eabi-  | --> |            |
| main.c        |     |      gcc        |     | main.o       |     |      ld         |     | blink.elf  |
| startup.c     |     |                 |     | startup.o    |     |                 |     |            |
+---------------+     +------------------+     +--------------+     +------------------+     +------------+
                                                                          ^
                                                                          |
                                                             +------------------------+
                                                             |    linker_script.ld   |
                                                             | (Memory layout config) |
                                                             +------------------------+
```

The compilation process involves these main steps:

1. **Source Files**: Your C code (`main.c`) and startup code (`startup.s`)
2. **Compiler**: Converts source files into object files using arm-none-eabi-gcc
3. **Object Files**: Generated machine code that still needs to be linked
4. **Linker**: Combines object files and arranges code in memory according to linker_script.ld
5. **Output**: Final executable (blink.elf) that can be flashed to the microcontroller

## Basic Program Structure

```c
#include <stdint.h>

// Function prototypes
void SystemInit(void);
void main(void);

// System initialization
void SystemInit(void)
{
    // Initialize system clock
    // Configure flash latency
    // Other system configurations
}

// Main program
void main(void)
{
    // Initialize peripherals
    // Main program loop
    while(1)
    {
        // Your code here
    }
}
```

## Common Pitfalls
1. Forgetting to initialize the stack pointer
2. Not clearing the .bss section
3. Not copying .data section from flash to RAM
4. Incorrect memory addresses in linker script
5. Missing interrupt handlers in vector table

## Best Practices
1. Always initialize variables
2. Use volatile for hardware registers
3. Implement all required interrupt handlers
4. Keep interrupt handlers short
5. Use proper memory barriers when needed
6. Document hardware register usage 