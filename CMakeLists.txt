cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SAMPLER VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SAMPLER 
    src/main.cpp 
    src/app.cpp
    src/memory.cpp
    src/logger.cpp
    src/terminal.cpp
    src/utils.cpp
)

# Specify any additional include directories
target_include_directories(SAMPLER PRIVATE src)

# Optionally, set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET SAMPLER POST_BUILD
    COMMAND scp $<TARGET_FILE:SAMPLER> pi@raspberry.local:~/
    COMMENT "Copying SAMPLER to Raspberry Pi (pi@raspberry.local:~)"
)