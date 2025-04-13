# Makefile to compile and link code for STM32F446RE

# Compiler and options configuration
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -Wl,--no-warn-rwx-segments
LDFLAGS = -T Linker_script/linker_script.ld

# Include files
CPPFLAGS = 	-D STM32F446xx \
			-I CMSIS/Device/Include \
			-I CMSIS/Core

# Source files
SRCS = 	Src/main.c \
		Startup/startup.c \
		CMSIS/Device/Source/system_stm32f4xx.c

OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = blink.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"

ex-flash: clean all flash