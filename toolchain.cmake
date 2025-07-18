# toolchain.cmake for Raspberry Pi Zero (ARMv6)

# Set the path to your Raspberry Pi toolchain
set(RPI_TOOLS_PATH "$ENV{HOME}/tools/arm-bcm2708/arm-linux-gnueabihf")

# The name of the target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the sysroot and cross compiler
set(CMAKE_SYSROOT "${RPI_TOOLS_PATH}/arm-linux-gnueabihf/sysroot")
set(CMAKE_C_COMPILER   "${RPI_TOOLS_PATH}/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${RPI_TOOLS_PATH}/bin/arm-linux-gnueabihf-g++")

# Where is the target environment
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Optional: Set compiler flags for ARMv6 (Pi Zero)
set(CMAKE_C_FLAGS   "-march=armv6 -mfpu=vfp -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "-march=armv6 -mfpu=vfp -mfloat-abi=hard")
