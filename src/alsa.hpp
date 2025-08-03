#pragma once

namespace smpl
{
    class logger;
    class memory;
    class terminal;
}

namespace smpl
{
class alsa_io
{
public:
    alsa_io(logger& _log);
    ~alsa_io();

    bool init(memory& memory, terminal& terminal);
private:
    logger& log;
};
}