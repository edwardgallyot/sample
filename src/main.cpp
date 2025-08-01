#include "app.hpp"
#include "logger.hpp"
#include "memory.hpp"

int main(int argc, char** argv)
{
    using namespace Sampler;
    auto app = App();
    if (!app.Run())
    {
        Logger::LogError("App ran unsuccessfully");
    }

    Logger::LogInfo("Ran successfully");
    return 0;
}
