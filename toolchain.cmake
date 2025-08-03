# toolchain.cmake for Raspberry Pi Zero (ARMv6)


# Set the path to your Raspberry Pi toolchain
set(RPI_TOOLS_PATH "$ENV{HOME}/x-tools/arm-RPI-linux-gnueabihf")

# The name of the target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT "${RPI_TOOLS_PATH}/arm-RPI-linux-gnueabihf/sysroot")
set(CMAKE_C_COMPILER   "${RPI_TOOLS_PATH}/bin/arm-RPI-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${RPI_TOOLS_PATH}/bin/arm-RPI-linux-gnueabihf-g++")

# Where is the target environment
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Optional: Set compiler flags for ARMv6 (Pi Zero)
set(CMAKE_C_FLAGS   "-march=armv6 -mfpu=vfp -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "-march=armv6 -mfpu=vfp -mfloat-abi=hard")
