# Makefile to run CMake with a specific toolchain file

# Variables
CMAKE_TOOLCHAIN_FILE = ../gcc-arm-none-eabi.cmake
BUILD_DIR = build
EXECUTABLE_FILE = blink
OPNEOCD_PATHS = -f interface/stlink.cfg -f target/stm32f4x.cfg

# Targets
all: cmake make

cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE) ..

make:
	$(MAKE) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all cmake clean

flash:
	openocd $(OPNEOCD_PATHS) -c "program $(BUILD_DIR)/$(EXECUTABLE_FILE).elf verify reset exit"

