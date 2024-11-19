# Makefile to compile and link code for STM32F446RE

# Compiler and options configuration
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -Wl,--no-warn-rwx-segments
LDFLAGS = -T linker_script.ld

# Source files
SRCS = main.c startup.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = blink.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"

ex-flash: clean all flash