# Makefile to compile and link code for STM32F446RE

# Compiler and options configuration
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -g -O0 -Wl,--no-warn-rwx-segments
ASFLAGS = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T Linker_script/linker_script.ld -nostdlib

# Include files
CPPFLAGS = 	-D STM32F446xx \
			-I CMSIS/Device/Include \
			-I CMSIS/Core

# Source files
SRCS = 	Src/main.c \
		CMSIS/Device/Source/system_stm32f4xx.c

ASRCS = Startup/startup.s

OBJS = $(ASRCS:.s=.o) $(SRCS:.c=.o)

# Executable name
TARGET = blink.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"

ex-flash: clean all flash