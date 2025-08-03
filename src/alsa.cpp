#include "alsa.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "terminal.hpp"
#include <cstdio>

using namespace smpl;

alsa_io::alsa_io(logger& _log)
    : log(_log)
{
}

alsa_io::~alsa_io()
{

}

static void some_cool_command(const char* s, void* context)
{
    printf("Command!\n");
}

bool alsa_io::init(memory& memory, terminal& terminal)
{
    terminal.add_cmd("Cool", "Some Cool Beanz", some_cool_command, this);

    return true;
}
