#include <cstdio>
#include "alsa.hpp"
#include "logger.hpp"
#include <alsa/asoundlib.h>

using namespace smpl;

alsa_io::alsa_io(logger& _log)
    : log(_log)
{
}

alsa_io::~alsa_io()
{

}

static void enumerate_devices(const char* s, void* context)
{
    alsa_io* alsa = reinterpret_cast<alsa_io*>(context);

    printf("Command!\n");
}

bool alsa_io::init(memory& memory, terminal& term)
{
    term.add_cmd("ALSA", "Alsa IO commands", enumerate_devices, this);

    return true;
}
