
#include "terminal.hpp"
#include <cstddef>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <termios.h>

using namespace Smpl;

Terminal::Terminal()
    : 
    commands(nullptr),
    commandsSize(0),
    commandsCount(0),
    inputBuffer(nullptr),
    inputCount(0),
    inputBufferSize(0)
{
}

Terminal::~Terminal()
{
}


bool Terminal::Init(Logger& logger, Memory& memory, u32 numCommands)
{
    // Allocate command memory
    this->commandsSize = numCommands * sizeof(Cmd);
    this->commands = memory.Push<Cmd>(numCommands);
    if (!this->commands)
    {
        logger.LogError("Couldn't allocate commands buffer of size: %u", this->commandsSize);
        this->commandsSize = 0;
        return false;
    }

    // Allocate input buffer memory
    this->inputBufferSize = 512;
    this->inputBuffer = memory.Push<char>(this->inputBufferSize);
    if (!this->inputBuffer)
    {
        logger.LogError("Couldn't allocate input buffer of size: %u", this->inputBufferSize);
        this->inputBufferSize = 0;
        return false;
    }

    memset(this->inputBuffer, 0, this->inputBufferSize);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    struct termios term;
    tcgetattr(fileno(stdin), &term);

    term.c_lflag &= ~(ECHO | ICANON);  // Turn off echo and canonical mode
    tcsetattr(fileno(stdin), 0, &term);

    return true;
}

bool Terminal::AddCmd(const char* name, const char* help, void (*callback)(const char*, void*), void* context = nullptr)
{
    if (this->commandsCount >= this->commandsSize)
    {
        return false;
    }
    this->commands[this->commandsCount].name = name;
    this->commands[this->commandsCount].help = help;
    this->commands[this->commandsCount].callback = callback;
    this->commands[this->commandsCount].context = context;
    this->commandsCount++;
    return true;
}

void Terminal::Welcome()
{
    fputc('>', stdout);
}

bool Terminal::HandleIoNonBlocking()
{
    int c = getc(stdin);

    if (c == EOF) 
    {
        return true;
    }

    fputc(c, stdout);

    if (c == '\n') 
    {
        size_t inputSplit = 0;
        {
            size_t in = 0;
            for (in = 0; in < this->inputCount; ++in)
            {
                char input = inputBuffer[in];
                if (input == ' ' || input == 0)
                {
                    break;
                }
            }
            inputSplit = in;
        }

        bool foundMatch = false;
        bool hasInput = this->inputCount > 0;
        if (hasInput)
        {
            for (size_t cmd = 0; cmd < this->commandsCount; ++cmd)
            {
                auto& command = this->commands[cmd];
            
                foundMatch = strncmp(command.name, this->inputBuffer, inputSplit) == 0;
                if (foundMatch)
                {
                    command.callback(inputBuffer + inputSplit, command.context);
                    break;
                }
            }
        }

        if (hasInput && !foundMatch)
        {
            printf("Command not found!\n");
        }

        memset(this->inputBuffer, 0, this->inputBufferSize);
        this->inputCount = 0;
        fputc('>', stdout);
        return true;
    }

    if (inputCount >= inputBufferSize)
    {
        printf("OVERFLOW\n");
        return false;
    }
   
    this->inputBuffer[this->inputCount] = c; 
    this->inputCount++;

    return true;
}