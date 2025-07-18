#include "miniaudio_backend.hpp"
#include <iostream>

MiniaudioBackend::MiniaudioBackend() 
    : initialized(false)
    , playbackDeviceInfos(nullptr)
    , playbackDeviceCount(0)
    , captureDeviceInfos(nullptr)
    , captureDeviceCount(0)
    , devicesEnumerated(false) {
}

MiniaudioBackend::~MiniaudioBackend() {
    shutdown();
}

bool MiniaudioBackend::initialize() {
    if (initialized) {
        return true;
    }
    
    ma_result result = ma_context_init(NULL, 0, NULL, &context);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to initialize miniaudio context" << std::endl;
        return false;
    }
    
    initialized = true;
    return true;
}

void MiniaudioBackend::shutdown() {
    if (initialized) {
        ma_context_uninit(&context);
        initialized = false;
    }
    
    // Reset device enumeration state
    playbackDeviceInfos = nullptr;
    playbackDeviceCount = 0;
    captureDeviceInfos = nullptr;
    captureDeviceCount = 0;
    devicesEnumerated = false;
}

void MiniaudioBackend::enumerateDevices() {
    if (devicesEnumerated) {
        return;
    }
    
    if (!initialized) {
        if (!initialize()) {
            return;
        }
    }
    
    ma_result result = ma_context_get_devices(
        &context,
        &playbackDeviceInfos,
        &playbackDeviceCount,
        &captureDeviceInfos,
        &captureDeviceCount);
    
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to enumerate devices" << std::endl;
        return;
    }
    
    devicesEnumerated = true;
}

void MiniaudioBackend::printDeviceInfo() {
    enumerateDevices();
    
    std::cout << "=== Capture Devices ===" << std::endl;
    for (ma_uint32 i = 0; i < captureDeviceCount; ++i) {
        std::cout << "Capture Device " << i << ":" << std::endl;
        std::cout << "  Name: " << captureDeviceInfos[i].name << std::endl;
        std::cout << "  ID: " << captureDeviceInfos[i].id.alsa << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "=== Playback Devices ===" << std::endl;
    for (ma_uint32 i = 0; i < playbackDeviceCount; ++i) {
        std::cout << "Playback Device " << i << ":" << std::endl;
        std::cout << "  Name: " << playbackDeviceInfos[i].name << std::endl;
        std::cout << "  ID: " << playbackDeviceInfos[i].id.alsa << std::endl;
        std::cout << std::endl;
    }
} 