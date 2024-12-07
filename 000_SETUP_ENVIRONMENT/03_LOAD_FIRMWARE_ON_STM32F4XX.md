## Load firmware on the STM32F4XX board (HELLO WORLD).

In this guide, we will use OpenOCD to load the firmware onto the STM32F4xx board. We will use a minimal template to create the binary and write a program that will make one of the onboard LEDs on the STM32F4xx blink.

### Prerequisites

### 1. Guide - [Steps to Connect STM32F4xx Board to WSL2 and Ubuntu]
Make sure the STM32F4XX board is connected to WSL2/Ubuntu. If it is not yet connected, you can follow this guide: [here](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_setup/000_SETUP_ENVIRONMENT/02_CONNECT_STM32F4XX_TO_WSL_AND_UBUNTU.md). If it is already set up, you can continue from step 3-Usage.

### 2. Install OpenOCD

follow these steps to install it:

```bash
#Ubuntu Terminal
sudo apt update
sudo apt install openocd
```

[Retun to Menu](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/blob/rework_setup/000_SETUP_ENVIRONMENT/README.md)