## Summary
Using the minimal files to compile and load a program onto the STM32F446RE board, in this case, a blinker.

Commands created in the Makefile to execute the code:
- 'make all'
compiles the files and generates the elf file.
- 'make clean'
deletes all object files and the elf file.
- 'make flash'
loads the elf file onto the board.
- 'make ex-flash'
executes the previous commands in the following order: clean, all, and flash.
