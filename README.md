# SMT32F446RE REPOSITORY

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