
# ARM GNU Toolchain Setup Guide

This guide provides step-by-step instructions to set up the ARM GNU Toolchain (version 13.3) on an Ubuntu system running in WSL2 (Windows Subsystem for Linux 2). Additionally, it covers the installation of Python 3.8 and the resolution of library dependency issues.

## Prerequisites

### 1. Install WSL2

Before proceeding, make sure that you have WSL2 installed on your Windows machine. If you don't have WSL2 installed, follow the official guide to set it up:

- [WSL Installation Guide](https://docs.microsoft.com/en-us/windows/wsl/install)

Once WSL2 is installed, you can set up an Ubuntu distribution inside WSL2.

### 2. Install Python 3.8

If you don't have Python 3.8 installed, follow these steps to install it:

```bash
sudo apt update
sudo apt upgrade
sudo add-apt-repository ppa:deadsnakes/ppa -y
sudo apt update
sudo apt install python3.8
python3.8 --version
```

This ensures that Python 3.8 is installed and ready to use.

---

## 1. Download the ARM Toolchain

Download the ARM GNU Toolchain package from the official website:

```bash
wget https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz
```

---

## 2. Extract the Toolchain to `/opt`

Extract the downloaded `.tar.xz` file to the `/opt` directory:

```bash
sudo tar xJf arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/
```

Rename the extracted folder for easier access:

```bash
sudo mv /opt/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi /opt/arm-gnu-toolchain
```

---

## 3. Configure the Global PATH

Add the `bin` directory of the toolchain to the system's global PATH, allowing access to the tools from any terminal session without needing to create symbolic links.

1. Create a configuration file for the toolchain:

```bash
sudo nano /etc/profile.d/arm-toolchain.sh
```

2. Inside the file, add the following line:

```bash
export PATH=/opt/arm-gnu-toolchain/bin:$PATH
```

3. Save the file, make it executable, and apply the changes:

```bash
sudo chmod +x /etc/profile.d/arm-toolchain.sh
source /etc/profile
```

---

## 4. Install Required Dependencies

The toolchain relies on certain libraries like `libncurses` and `libtinfo`. Install them using the following commands:

```bash
sudo apt install libncurses-dev
sudo apt install libtinfo-dev
```

---

## 5. Resolve Issues with `libtinfo` and `libncurses` (Symbolic Links)

If `arm-none-eabi-gdb` throws errors related to `libtinfo.so.5` or `libncursesw.so.5`, it is due to modern versions of Ubuntu using version 6 of these libraries. You need to create symbolic links to make `gdb` work properly.

1. Create the necessary symbolic links:

```bash
sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6 /usr/lib/x86_64-linux-gnu/libncursesw.so.5
```

2. Verify that the symbolic links were created successfully:

```bash
ls -l /usr/lib/x86_64-linux-gnu/libtinfo.so.5
ls -l /usr/lib/x86_64-linux-gnu/libncursesw.so.5
```

---

## 6. Verify the Toolchain Installation

Finally, verify that the toolchain is correctly installed by checking the versions of the tools:

```bash
arm-none-eabi-gcc --version
arm-none-eabi-g++ --version
arm-none-eabi-gdb --version
arm-none-eabi-size --version
```

If all tools return their version information correctly, the setup is complete!

---

## Troubleshooting

If you encounter any issues during installation, ensure that all dependencies are properly installed and that the symbolic links are correctly created. Additionally, check for missing libraries or any error messages during the setup process.
