#pragma once

#include "logger.hpp"
#include "terminal.hpp"

namespace Smpl
{
class Alsa
{
public:
    Alsa(Logger& logger);
    ~Alsa();

    bool Init(Memory& memory, Terminal& terminal);
private:
    Logger& logger;
};
}