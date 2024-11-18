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

   Bind the device:
   ```powershell
   usbipd bind --busid <DEVICE-ID>
   ```

   Attach the device to WSL:
   ```powershell
   usbipd attach --wsl --busid <DEVICE-ID>
   ```

4. **Verify on Ubuntu WSL2**

   Check if the device is detected:
   ```bash
   lsusb
   ```

---

## Troubleshooting

you can send me a msg on Instagram for any question, I respond quickly [0xF06](https://www.instagram.com/0xf06/)