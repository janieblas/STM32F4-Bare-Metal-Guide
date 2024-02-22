# SMT32F446RE REPOSITORY

## SUMMARY
With this repository, I want to demonstrate how to set up a project to program an STM32F446RE board without using STM32CubeIDE. This involves using a Linux (Ubuntu) virtual machine and VSCode on Windows with SSH. Starting with a minimal 'bare-metal' example and gradually adding standard libraries to create a more complex project. I hope this can help you in some way.

## STM32F446RE BOARD
<img src="NUCLEO-F446RE.jpg" alt="NUCLEO-F446RE" style="width:50%;">

## UBUNTU
For the exercises, Ubuntu 22.04.3 LTS was used in the VirtualBox virtual machine.

## TOOLCHAIN
Toolchain version: arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi
- [Download](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [Manual installation](https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa)

Note: I had to change the Python version for the ARM toolchain to work. [Foro with the problem](https://community.arm.com/support-forums/f/compilers-and-libraries-forum/53996/arm-gnu-toolchain-12-2-rel1-x86_64-arm-none-eabi-gdb-fails-on-ubuntu-22-04/180229#180229)

OpenOCD was installed to load programs onto the board.
[OpenOCD](https://openocd.org/pages/about.html)

To facilitate compilation, Makefiles and CMake are used.

## VSCODE Extensions
- [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh)
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
- [Serial Monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor)