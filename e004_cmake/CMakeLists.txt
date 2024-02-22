cmake_minimum_required(VERSION 3.15)

# Project name
project(blink C ASM)

set(EXECUTABLE ${CMAKE_PROJECT_NAME})

set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -nostdlib
    -g
    -O0
    -Wl,--no-warn-rwx-segments)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Startup/startup.c )
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Linker_script/linker_script.ld)

# Headers files
set(INCS
    CMSIS/Device/Include
    CMSIS/Core
)

# Source files
set(SRCS
    Src/main.c
    Startup/startup.c
    CMSIS/Device/Source/system_stm32f4xx.c
)

# Executable files
add_executable(${EXECUTABLE}
    ${SRCS}
    ${STARTUP_SCRIPT})

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    STM32F446xx)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${INCS})

target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS})

target_link_options(${EXECUTABLE} PRIVATE
    -T ${LINKER_SCRIPT}
    ${CPU_PARAMETERS})

