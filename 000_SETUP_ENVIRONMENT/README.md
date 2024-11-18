
# ARM GNU Toolchain Setup Guide

This guide provides step-by-step instructions to set up the ARM GNU Toolchain (version 13.3 or others) on an Ubuntu (20 to 24) system running in WSL2 (Windows Subsystem for Linux 2). Additionally, it covers the installation of Python 3.8 and the resolution of library dependency issues.

## Prerequisites

### 1. Install WSL2 with Ubuntu (20 to 24)

Before proceeding, make sure that you have WSL2 installed on your Windows machine. Once WSL2 is installed, you can set up an Ubuntu (20 to 24) distribution inside WSL2.

I recommend you that check videos on Youtube for the installation.

### 2. Install Python 3.8

The installation of Python 3.8 is necessary because a bug with newer Python versions has been reported, affecting gdb from the ARM toolchain, specifically on Ubuntu 20 onwards. This issue causes Python-related errors when running gdb, such as missing dependencies or issues with the Python environment configuration. The solution to this problem is downgrading to Python 3.8, which resolves these compatibility issues and ensures that gdb runs smoothly without Python errors.

forum: [arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi gdb fails on Ubuntu 22.04](https://community.arm.com/support-forums/f/compilers-and-libraries-forum/53996/arm-gnu-toolchain-12-2-rel1-x86_64-arm-none-eabi-gdb-fails-on-ubuntu-22-04/180229#180229)

If you don't have Python 3.8 installed, follow these steps to install it:

```bash
#Ubuntu Terminal
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
#Ubuntu Terminal
wget https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz
```

if you need another version, this is the link: [Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

---

## 2. Extract the Toolchain to `/opt`

Extract the downloaded `.tar.xz` file to the `/opt` directory:

```bash
#Ubuntu Terminal
sudo tar xJf arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/
```

Rename the extracted folder for easier access:

```bash
#Ubuntu Terminal
sudo mv /opt/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi /opt/arm-gnu-toolchain
```

---

## 3. Configure the Global PATH

Add the `bin` directory of the toolchain to the system's global PATH, allowing access to the tools from any terminal session without needing to create symbolic links.

1. Create a configuration file for the toolchain:

```bash
#Ubuntu Terminal
sudo nano /etc/profile.d/arm-toolchain.sh
```

2. Inside the file, add the following line:

```bash
#Ubuntu Terminal
export PATH=/opt/arm-gnu-toolchain/bin:$PATH
```

After entering the line 'export', press CTRL+O to save the file Then, press Enter to confirm the file name. Press CTRL+X to exit the editor.

3. Make it executable, and apply the changes:

```bash
#Ubuntu Terminal
sudo chmod +x /etc/profile.d/arm-toolchain.sh
source /etc/profile
```

---

## 4. Install Required Dependencies

The toolchain relies on certain libraries like `libncurses` and `libtinfo`. Install them using the following commands:

```bash
#Ubuntu Terminal
sudo apt install libncurses-dev
sudo apt install libtinfo-dev
```

---

## 5. Resolve Issues with `libtinfo` and `libncurses` (Symbolic Links)

`arm-none-eabi-gdb` throws errors related to `libtinfo.so.5` and `libncursesw.so.5`, this is because modern versions of Ubuntu use version 6 of these libraries. You need to create symlinks for `gdb` to work properly.

1. Create the necessary symbolic links:

```bash
#Ubuntu Terminal
sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6 /usr/lib/x86_64-linux-gnu/libncursesw.so.5
```

2. Verify that the symbolic links were created successfully:

```bash
#Ubuntu Terminal
ls -l /usr/lib/x86_64-linux-gnu/libtinfo.so.5
ls -l /usr/lib/x86_64-linux-gnu/libncursesw.so.5
```

---

## 6. Verify the Toolchain Installation

Finally, verify that the toolchain is correctly installed by checking the versions of the tools:

```bash
#Ubuntu Terminal
arm-none-eabi-gcc --version
arm-none-eabi-g++ --version
arm-none-eabi-gdb --version
arm-none-eabi-size --version
```

If all tools return their version information correctly, the setup is complete!

---

## Troubleshooting

If you encounter any issues during installation, ensure that all dependencies are properly installed and that the symbolic links are correctly created. Additionally, check for missing libraries or any error messages during the setup process.

you can send me a msg on Instagram for any question, I respond quickly [0xF06](https://www.instagram.com/0xf06/)
