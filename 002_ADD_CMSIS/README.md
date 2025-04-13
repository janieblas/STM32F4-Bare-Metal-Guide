## Summary
This exercise added the CMSIS folder.
What is CMSIS?
CMSIS provides a hardware abstraction layer and a set of reusable software components for microcontrollers based on ARM Cortex-M.
 
We used two repositories, [CMSIS_5](https://github.com/ARM-software/CMSIS_5) and [CMSIS_Device_F4](https://github.com/STMicroelectronics/cmsis_device_f4)'.

- CMSIS_5: We utilized CMSIS-CORE, which defines register access interfaces and processor intrinsic functions, allowing efficient and direct handling of the processor, its special registers, and features. This includes the interrupt system, memory access, and more. Only the files from the CMSIS/Core folder were extracted from this repository.
- CMSIS_Device_F4: This repository is specifically for STM32F4 devices and contains register definitions, memory addresses, and other specific hardware configurations for STM32F4 series microcontrollers. This includes startup files, system files, and more, which are specific to these devices. Only the files from the CMSIS/Device folder were extracted from this repository.

Commands created in the Makefile to execute the code:
- 'make all'
compiles the files and generates the elf file.
- 'make clean'
deletes all object files and the elf file.
- 'make flash'
loads the elf file onto the board.
- 'make ex-flash'
executes the previous commands in the following order: clean, all, and flash.
