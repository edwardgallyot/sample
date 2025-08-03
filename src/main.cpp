#include "app.hpp"
#include "logger.hpp"
#include "memory.hpp"

int main(int argc, char** argv)
{
    using namespace smpl;
    auto logger_instance = logger("APP");
    auto app_instance = app(logger_instance);
    if (!app_instance.run())
    {
        logger_instance.log_error("App ran unsuccessfully");
        return 1;
    }

    logger_instance.log_info("Ran successfully");
    return 0;
}
