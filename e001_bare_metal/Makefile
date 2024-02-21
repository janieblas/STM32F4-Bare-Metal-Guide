# Makefile para compilar y enlazar el código para STM32F446RE

# Configuración del compilador y opciones
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -Wl,--no-warn-rwx-segments
LDFLAGS = -T linker_script.ld

# Archivos fuente
SRCS = main.c startup.c
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
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