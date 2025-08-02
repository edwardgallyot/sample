#include "app.hpp"
#include "memory.hpp"
#include "logger.hpp"
#include "utils.hpp"

using namespace Smpl;

App::App(Logger& _logger)
: isRunning(false),
    logger(_logger),
    memory(_logger),
    terminal(),
    alsa(_logger)
{
}

App::~App()
{

}

bool App::Run()
{
    const size_t appMemorySize = Utils::Megabytes(512);

    bool success = this->memory.Allocate(appMemorySize);
    if (!success)
    {
        this->logger.LogError( "Memory failed to intialise");
        return false;
    }

    const u32 maxCommands = 1024;
    success = this->terminal.Init(this->logger, this->memory, maxCommands);
    if (!success)
    {
        this->logger.LogError( "Terminal failed to allocate");
        return false;
    }

    this->logger.LogInfo( "App intialised successfully");

    this->logger.LogInfo( "Set isRunning to true.");
    this->isRunning = true;

    this->alsa.Init(this->memory, this->terminal);

    this->logger.LogInfo("Beginning main loop.");

    terminal.Welcome();

    while (this->isRunning)
    {
        if (!this->terminal.HandleIoNonBlocking())
        {
            this->logger.LogError("Error handling terminal IO");
        }
    }
    return true;
}
