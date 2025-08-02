#include "alsa.hpp"
#include <cstdio>

using namespace Smpl;

Alsa::Alsa(Logger& _logger)
    : logger(_logger)
{
}

Alsa::~Alsa()
{

}

static void SomeCoolCommand(const char* s, void* context)
{
    printf("Command!\n");
}

bool Alsa::Init(Memory& memory, Terminal& terminal)
{
    terminal.AddCmd("Cool", "Some Cool Beanz", SomeCoolCommand, this);

    return true;
}
