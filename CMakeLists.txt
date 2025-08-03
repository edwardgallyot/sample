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
    src/alsa.cpp
)

# Specify any additional include directories
target_include_directories(SAMPLER PRIVATE 
    ./src
    ./alsa-lib/include
)

target_link_libraries(SAMPLER PRIVATE 
    ${CMAKE_SOURCE_DIR}/alsa-lib/src/.libs/libasound.so
)

# Optionally, set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET SAMPLER POST_BUILD
    COMMAND scp $<TARGET_FILE:SAMPLER> pi@raspberry.local:~/
    COMMENT "Copying SAMPLER to Raspberry Pi (pi@raspberry.local:~)"
)

# Copy source folder to Raspberry Pi
add_custom_command(TARGET SAMPLER POST_BUILD
    COMMAND scp -r ${CMAKE_SOURCE_DIR}/src pi@raspberry.local:~/
    COMMENT "Copying source folder to Raspberry Pi (pi@raspberry.local:~/src)"
)

# Add remote cleanup command that runs during clean
add_custom_command(TARGET SAMPLER PRE_BUILD
    COMMAND ssh pi@raspberry.local "rm -f ~/SAMPLER && rm -rf ~/src" 2>/dev/null || true
    COMMENT "Cleaning remote files before build"
)
