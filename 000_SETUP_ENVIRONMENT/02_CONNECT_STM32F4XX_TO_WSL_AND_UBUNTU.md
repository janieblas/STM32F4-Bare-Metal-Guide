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
   ```
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

## Automatic USB Connection Script

For convenience, you can use an automatic PowerShell script to connect your STM32 device to WSL. Save the script below as `attach-usb-to-wsl.ps1`:

```powershell
# USB Device to WSL Attachment Script
# This script automates listing USB devices, binding, and attaching to WSL

# Run as Administrator
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Warning "This script requires Administrator privileges. Please run as Administrator."
    exit
}

# Function to list available USB devices
function List-USBDevices {
    Write-Host "`nListing available USB devices...`n" -ForegroundColor Cyan
    $devices = usbipd list
    $devices | ForEach-Object { Write-Host $_ }
    return $devices
}

# List the devices initially
$deviceList = List-USBDevices

# Prompt for BUSID
$busid = Read-Host "`nEnter the BUSID of the device you want to attach to WSL (e.g., 6-3)"

# Validate input
if ([string]::IsNullOrWhiteSpace($busid)) {
    Write-Host "No BUSID provided. Exiting script." -ForegroundColor Red
    exit
}

# Bind the device
Write-Host "`nBinding device with BUSID $busid..." -ForegroundColor Cyan
try {
    $bindResult = usbipd bind --busid $busid
    Write-Host $bindResult -ForegroundColor Green
}
catch {
    Write-Host "Error binding device: $_" -ForegroundColor Red
    exit
}

# Attach the device to WSL
Write-Host "`nAttaching device with BUSID $busid to WSL..." -ForegroundColor Cyan
try {
    $attachResult = usbipd attach --wsl --busid $busid
    Write-Host $attachResult -ForegroundColor Green
    
    Write-Host "`nUSB device with BUSID $busid has been successfully attached to WSL." -ForegroundColor Green
    Write-Host "You can now access the device from your WSL distribution." -ForegroundColor Green
}
catch {
    Write-Host "Error attaching device to WSL: $_" -ForegroundColor Red
}
```

### How to use the automatic script:

1. **Save the script** as `attach-usb-to-wsl.ps1`
2. **Run PowerShell as Administrator**
3. **Navigate to the script location**: `cd path\to\script\folder`
4. **Run the script**: 
   ```powershell
   # If you encounter execution policy errors, first run:
   Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
   
   # Then run the script:
   .\attach-usb-to-wsl.ps1
   ```
5. **Follow the prompts** to select your STM32 device

The script will automatically list devices, bind the selected device, and attach it to your WSL environment.

---

## Troubleshooting

You can send me a message on Instagram for any question, I respond quickly [0xF06](https://www.instagram.com/0xf06/)

[Return to Menu](https://github.com/janieblas/STM32F446E_whitout_stm32CubeIDE/tree/main/000_SETUP_ENVIRONMENT)