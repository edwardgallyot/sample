#pragma once

#include "terminal.hpp"
#include "memory.hpp"

namespace smpl
{
class alsa_io
{
public:
    alsa_io(logger& _log);
    ~alsa_io();

    bool init(utils::memory& memory, terminal& terminal);
private:
    logger& log;
};
}
