#include "audio_backend/miniaudio_backend.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    MiniaudioBackend audioBackend;
    
    if (!audioBackend.initialize()) {
        std::cerr << "Failed to initialize audio backend" << std::endl;
        return -1;
    }
    
    audioBackend.printDeviceInfo();
    
    return 0;
}
