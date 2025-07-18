cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SAMPLER VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MINIAUDIO_ENABLE_ALSA ON CACHE BOOL "Enable ALSA backend in miniaudio")
set(MINIAUDIO_NO_EXTRA_NODES ON CACHE BOOL "Disable extra node graph nodes in miniaudio")
set(MINIAUDIO_NO_NODE_GRAPH ON CACHE BOOL "Disable node graph in miniaudio")

add_subdirectory(lib/miniaudio)

# Add the executable
add_executable(SAMPLER src/main.cpp src/audio_backend/miniaudio_backend.cpp)

target_link_libraries(SAMPLER PRIVATE miniaudio pthread dl)

# Specify any additional include directories
# target_include_directories(MyRaspberryPiExecutable PRIVATE /path/to/include)

# Optionally, set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET SAMPLER POST_BUILD
    COMMAND scp $<TARGET_FILE:SAMPLER> pi@raspberry.local:~/
    COMMENT "Copying SAMPLER to Raspberry Pi (pi@raspberry.local:~)"
)