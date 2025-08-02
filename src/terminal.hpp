#pragma once

#include "memory.hpp"
#include "types.hpp"

namespace Smpl
{
class Terminal
{
public: 

    Terminal();
    ~Terminal();

    bool Init(Logger& logger, Memory& memory, u32 numCommands);
    bool AddCmd(const char* name, const char* help, void (*callback)(const char*, void*), void* context);
    void Welcome();
    bool HandleIoNonBlocking();
private:
    struct Cmd
    {
        const char* name;
        const char* help;
        void (*callback)(const char*, void*);
        void* context;
    };

    Cmd*    commands;
    size_t  commandsSize;
    size_t  commandsCount;

    char*  inputBuffer;
    size_t inputCount;
    size_t inputBufferSize;
};
}