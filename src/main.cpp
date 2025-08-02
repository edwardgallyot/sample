#include "app.hpp"
#include "logger.hpp"
#include "memory.hpp"

int main(int argc, char** argv)
{
    using namespace Sampler;
    auto logger = Logger("APP");
    auto app = App(logger);
    if (!app.Run())
    {
        logger.LogError("App ran unsuccessfully");
        return 1;
    }

    logger.LogInfo("Ran successfully");
    return 0;
}
