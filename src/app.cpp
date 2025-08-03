#include "app.hpp"
#include "memory.hpp"
#include "logger.hpp"
#include "utils.hpp"
#include "terminal.hpp"
#include "alsa.hpp"

using namespace smpl;

app::app(logger& _log)
: is_running(false),
    log(_log),
    mem(_log),
    term(),
    alsa(_log)
{
}

app::~app()
{

}

bool app::run()
{
    const size_t app_memory_size = utils::megabytes(512);

    bool success = this->mem.allocate(app_memory_size);
    if (!success)
    {
        this->log.log_error( "Memory failed to intialise");
        return false;
    }

    const u32 max_commands = 1024;
    success = this->term.init(this->log, this->mem, max_commands);
    if (!success)
    {
        this->log.log_error( "Terminal failed to allocate");
        return false;
    }

    this->log.log_info( "App intialised successfully");

    this->log.log_info( "Set is_running to true.");
    this->is_running = true;

    this->alsa.init(this->mem, this->term);

    this->log.log_info("Beginning main loop.");

    term.welcome();

    while (this->is_running)
    {
        if (!this->term.handle_io_non_blocking())
        {
            this->log.log_error("Error handling terminal IO");
        }
    }
    return true;
}
