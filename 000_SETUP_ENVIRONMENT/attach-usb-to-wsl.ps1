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