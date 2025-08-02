#pragma once

#include "alsa.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "terminal.hpp"

namespace Smpl
{
class App 
{
public:
    App(Logger& logger);
    ~App();
    bool Run();
private:
    Logger& logger;
    Memory memory;
    Terminal terminal;
    Alsa alsa;
    bool isRunning;
};
}
