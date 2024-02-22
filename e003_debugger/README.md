## Summary
In this exercise, we modified the makefile to enable debugging of the code and configured the launch.json for debugging with OpenOCD.

We adjusted the flags when compiling using the makefile, adding "-g -O0".
```
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -g -O0 -Wl,--no-warn-rwx-segments
```

The options -g and -O0 are GCC compiler options that affect code generation and the information included in the resulting executable. These options are common when you are developing and debugging code.

Download the [OpenOCD](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) extension in VSCode.

Generate the file launch.json inside the .vscode folder. I used this configuration for debugging:
```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Cortex Debug",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/blink.elf",
            "request": "launch",
            "type": "cortex-debug",
            //"runToEntryPoint": "main",
            "servertype": "openocd",
            "device": "STM32F446RE",
            "configFiles": [
                "interface/stlink.cfg",
                "target/stm32f4x.cfg"
            ]
        }
    ]
}
```

Commands created in the Makefile to execute the code:
- 'make all'
compiles the files and generates the elf file.
- 'make clean'
deletes all object files and the elf file.
- 'make flash'
loads the elf file onto the board.
- 'make ex-flash'
executes the previous commands in the following order: clean, all, and flash.
