#include "app/app.hpp"

using namespace Sampler;

bool App::Init(App* app)
{
    const size_t appMemorySize = 1024;
    bool memoryIsInitialised = Sampler::Memory::Init(&app->memory, appMemorySize);
    if (!memoryIsInitialised)
    {
        return false;
    }
    return true;
}

bool App::Run()
{
    this->isRunning = true;

    while (this->isRunning)
    {
        // Do app stuff
    }

    return true;
}