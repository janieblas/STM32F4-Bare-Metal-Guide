cmake_minimum_required(VERSION 3.15)

# Project name
project(blink C ASM)

# Define the executable name as the project name
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

# Define processor-specific parameters
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -nostdlib
    -Wl,--no-warn-rwx-segments)

# Specify the location of the linker script
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld)

# Define header folders
set(INCS
    CMSIS/Include
    CMSIS/Core
)

# Define source files
set(SRCS
    main.c
    startup.c
    CMSIS/Source/system_stm32f4xx.c
)

# Executable files
add_executable(${EXECUTABLE}
    ${SRCS})

# Built-in Macros (defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    STM32F446xx)

# Add header directories 
target_include_directories(${EXECUTABLE} PRIVATE
    ${INCS})

# Target-specific compilation options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS})

# Target-specific linking options
target_link_options(${EXECUTABLE} PRIVATE
    -T ${LINKER_SCRIPT}
    ${CPU_PARAMETERS})

