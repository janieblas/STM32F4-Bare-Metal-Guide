## Steps to Connect STM32F4xx Board to WSL2 and Ubuntu

1. **Install USBIPD-WIN on Windows**

   Run PowerShell as administrator:
   ```powershell
   winget install --interactive --exact dorssel.usbipd-win
   ```

2. **Install USB Support on Ubuntu WSL2**

   In Ubuntu WSL2, run:
   ```bash
   sudo apt update
   sudo apt install linux-tools-generic hwdata
   sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20
   ```

   Install USB utilities:
   ```bash
   sudo apt install usbutils
   ```

3. **Usage**

   On Windows PowerShell (Admin), list available USB devices:
   ```powershell
   usbipd list
   ```
   Result:
   ```powershell
   PS C:\Users\52644> usbipd list
   Connected:
   BUSID  VID:PID    DEVICE  
   6-3    0483:374b  ST-Link Debug, USB Memmory Divice...  Shared
   ```

   Bind the device, In this case BUSID is 6-3:
   ```powershell
   usbipd bind --busid <BUSID>
   
   Result:
   ```powershell
   usbipd: info: Device with busid '6-3' was already shared.
   ```

   Attach the device to WSL:
   ```powershell
   usbipd attach --wsl --busid <BUSID>
   ```
   Result:
   ```powershell
  usbipd: info: Using WSL distribution 'Ubuntu-24.04' to attach; the device will be available in all WSL 2 distributions.
  usbipd: info: Using IP address 172.33.27.1 to reach the host.
   ```

4. **Verify on Ubuntu WSL2**

   Check if the device is detected:
   ```bash
   lsusb
   ```
   Result:
   ```bash
   Bus 001 Device 002: ID 0483:374b STMicroelectronics ST-LINK/V2.1
   ```
---

## Troubleshooting

you can send me a msg on Instagram for any question, I respond quickly [0xF06](https://www.instagram.com/0xf06/)