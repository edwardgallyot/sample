#pragma once

#include "miniaudio.h"
#include <iostream>

class MiniaudioBackend {
public:
    MiniaudioBackend();
    ~MiniaudioBackend();
    
    bool initialize();
    void shutdown();
    
    // Convenience method to print all device info
    void printDeviceInfo();

private:
    ma_context context;
    bool initialized;
    
    // Store device info to avoid repeated calls
    ma_device_info* playbackDeviceInfos;
    ma_uint32 playbackDeviceCount;
    ma_device_info* captureDeviceInfos;
    ma_uint32 captureDeviceCount;
    bool devicesEnumerated;
    
    void enumerateDevices();
}; 