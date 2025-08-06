#pragma once

#include "logger.hpp"
#include "memory.hpp"
#include "terminal.hpp"
#include "alsa.hpp"

namespace smpl
{
class app 
{
public:
    app(logger& logger);
    ~app();
    bool run();
private:
    logger& log;
    utils::memory mem;
    terminal term;
    alsa_io alsa;
    bool is_running;
};
}
