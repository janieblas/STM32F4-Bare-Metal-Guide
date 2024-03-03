# Makefile to run CMake with a specific toolchain file

# Variables
EXECUTABLE_FILE = blink
BUILD_DIR = build
CMAKE_TOOLCHAIN_FILE_PATH = ../gcc-arm-none-eabi.cmake
OPNEOCD_PATHS = -f interface/stlink.cfg -f target/stm32f4x.cfg

# Targets
all: cmake make

cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -D CMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE_PATH) ..

make:
	$(MAKE) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all cmake clean

flash:
	openocd $(OPNEOCD_PATHS) -c "program $(BUILD_DIR)/$(EXECUTABLE_FILE).elf verify reset exit"

