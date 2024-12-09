#!/bin/bash

VERSION="13.3.rel1"
DEST="/opt"
TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu/${VERSION}/binrel/arm-gnu-toolchain-${VERSION}-x86_64-arm-none-eabi.tar.xz"
FILENAME="arm-gnu-toolchain-${VERSION}-x86_64-arm-none-eabi.tar.xz"
DIRNAME="arm-gnu-toolchain-${VERSION}-x86_64-arm-none-eabi"

FILEPATH="${DEST}/${FILENAME}"

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

#########################################################################

# Verificar si Python 3.8 está instalado
if ! command -v python3.8 &>/dev/null; then
    echo "Python 3.8 no está instalado. Procediendo con la instalación..."
    sudo apt update
    sudo apt upgrade -y
    sudo add-apt-repository ppa:deadsnakes/ppa -y
    sudo apt update
    sudo apt install python3.8 -y
    echo -e "${GREEN}>> Python 3.8 se instaló correctamente. <<${NC}"
else
    echo -e "${YELLOW}>> Alerta: Python 3.8 ya está instalado. <<${NC}"
fi
# Verificar la versión de Python 3.8
python3.8 --version

#########################################################################

# Descargar el archivo si no existe
if [ ! -f "$FILEPATH" ]; then
    echo "Descargando archivo..."
    sudo wget -P $DEST $TOOLCHAIN_URL
    echo -e "${GREEN}>> el archivo fue descargado correctamente. <<${NC}"
else
    echo -e "${YELLOW}>> Alerta: El archivo ya existe en esta dirección <<${NC}"
fi

# Descomprimir el archivo
echo "Descomprimiendo archivo..."
sudo tar xJf $FILEPATH -C $DEST

# Cambiar el nombre de la carpeta
echo "Renombrando la carpeta..."
sudo mv "${DEST}/${DIRNAME}" "${DEST}/arm-gnu-toolchain"

# Verificación
if [ -d "${DEST}/arm-gnu-toolchain" ]; then
    echo -e "${GREEN}>> La carpeta fue renombrada correctamente. <<${NC}"
else
   echo -e "${RED}>> Error: Hubo un problema al renombrar la carpeta. <<${NC}"
    exit 1
fi

#########################################################################

# Configurar el PATH globalmente
echo "Configurando el PATH globalmente..."
CONFIG_FILE="/etc/profile.d/arm-toolchain.sh"
TOOLCHAIN_DIR="${DEST}/arm-gnu-toolchain"

# Crear el archivo de configuración con la línea de export
sudo bash -c "echo 'export PATH=${TOOLCHAIN_DIR}/bin:\$PATH' > $CONFIG_FILE"

# Verificar si el archivo fue creado correctamente
if [ -f "$CONFIG_FILE" ]; then
    echo -e "${GREEN}>> Archivo de configuración creado en $CONFIG_FILE. <<${NC}"
else
    echo -e "${RED}>> Error: No se pudo crear el archivo de configuración. <<${NC}"
    exit 1
fi

# Hacer ejecutable el archivo de configuración
echo "Haciendo ejecutable el archivo de configuración..."
sudo chmod +x "$CONFIG_FILE"

# Aplicar los cambios al PATH global
echo "Aplicando cambios..."
source "$CONFIG_FILE"

# Verificar si el PATH fue actualizado correctamente
if [[ ":$PATH:" == *":${TOOLCHAIN_DIR}/bin:"* ]]; then
    echo -e "${GREEN}>> PATH actualizado correctamente. Las herramientas están disponibles globalmente. <<${NC}"
else
    echo -e "${RED}>> Error: El PATH no se actualizó correctamente. <<${NC}"
    exit 1
fi

#########################################################################

# Instalar bibliotecas requeridas
echo "Instalando bibliotecas necesarias..."
sudo apt update
sudo apt install -y libncurses-dev libtinfo-dev

# Crear enlaces simbólicos para las bibliotecas
echo "Creando enlaces simbólicos para las bibliotecas..."
sudo ln -sf /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
sudo ln -sf /usr/lib/x86_64-linux-gnu/libncursesw.so.6 /usr/lib/x86_64-linux-gnu/libncursesw.so.5

# Verificar enlaces simbólicos
if [ -L "/usr/lib/x86_64-linux-gnu/libtinfo.so.5" ] && [ -L "/usr/lib/x86_64-linux-gnu/libncursesw.so.5" ]; then
    echo -e "${GREEN}>> Enlaces simbólicos creados correctamente. <<${NC}"
else
    echo -e "${RED}>> Error: No se pudieron crear los enlaces simbólicos. <<${NC}"
    exit 1
fi

# Verificar la instalación del toolchain
echo "Verificando instalación del toolchain..."
for cmd in gcc g++ gdb size; do
    if command -v arm-none-eabi-$cmd &>/dev/null; then
        echo -e "${GREEN}>> arm-none-eabi-$cmd está instalado: $(arm-none-eabi-$cmd --version | head -n 1) <<${NC}"
    else
        echo -e "${RED}>> Error: arm-none-eabi-$cmd no está instalado correctamente. <<${NC}"
        exit 1
    fi
done


#########################################################################
# OpenOCD Installation
echo -e "${GREEN}Instalando OpenOCD...${NC}"
sudo apt update && sudo apt install -y openocd

echo -e "${GREEN}Verificando instalación de OpenOCD...${NC}"
if command -v openocd &>/dev/null; then
    echo -e "${GREEN}>> OpenOCD está instalado: $(openocd --version | head -n 1) <<${NC}"
else
    echo -e "${RED}>> Error: OpenOCD no se instaló correctamente. <<${NC}"
    exit 1
fi

#########################################################################
# Install USB Support on Ubuntu WSL2
echo -e "${GREEN}Instalando soporte USB en Ubuntu WSL2...${NC}"
sudo apt update && sudo apt install -y linux-tools-generic hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20

echo -e "${GREEN}Verificando instalación del soporte USB...${NC}"
if command -v usbip &>/dev/null; then
    echo -e "${GREEN}>> Soporte USB instalado correctamente: $(usbip --version) <<${NC}"
else
    echo -e "${RED}>> Error: El soporte USB no se instaló correctamente. <<${NC}"
    exit 1
fi

#########################################################################
# Install USB utilities
echo -e "${GREEN}Instalando utilidades USB...${NC}"
sudo apt update && sudo apt install -y usbutils

echo -e "${GREEN}Verificando instalación de las utilidades USB...${NC}"
if command -v lsusb &>/dev/null; then
    echo -e "${GREEN}>> Utilidades USB instaladas correctamente: $(lsusb --version) <<${NC}"
else
    echo -e "${RED}>> Error: Las utilidades USB no se instalaron correctamente. <<${NC}"
    exit 1
fi

#########################################################################

echo -e "${GREEN}>> Toolchain configurado e instalado correctamente. <<${NC}"

# Reiniciar el shell para aplicar cambios
exec $SHELL
