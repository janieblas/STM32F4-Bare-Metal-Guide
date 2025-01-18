#### QUICK SETUP
You can run this script on Ubuntu terminal to install everything faster.

[toolchain_setup.sh](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_readme_main/000_SETUP_ENVIRONMENT/toolchain_setup.sh)

```Terminal
chmod +x toolchain_setup.sh
./toolchain_setup.sh
```

>[!NOTE]
By default I use version 13.3 of the ARM toolchain, you can change the version within the script.

You can continue with the board's connection "[Connect STM32F4xx Board to WSL2 and Ubuntu](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_readme_main/000_SETUP_ENVIRONMENT/02_CONNECT_STM32F4XX_TO_WSL_AND_UBUNTU.md)" if everything goes correctly.

-----------------------------------------------------------------------------------------


#### Setup Environment to use ARM Toolchain, WSL2 Ubuntu and STM32F4xx (step by step)
Guides to setting up the ARM development environment on Ubuntu, including dependency installation, PATH configuration, and troubleshooting common issues. Steps to connect an STM32F4 board in WSL2 and Ubuntu, covering necessary tools installation and USB connection verification 

Follow the steps:

| Num   |                   Title                           |
|:------|:-------------------------------------------------:|
|   1   |   [ARM GNU Toolchain Setup Guide](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_setup/000_SETUP_ENVIRONMENT/01_ARM_TOOLCHAIN.md)               | 
|   2   |   [Connect STM32F4xx Board to WSL2 and Ubuntu](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_readme_main/000_SETUP_ENVIRONMENT/02_CONNECT_STM32F4XX_TO_WSL_AND_UBUNTU.md)  | 