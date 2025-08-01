#include "app.hpp"
#include <cstdio>

using namespace Sampler;

App::App()
: m_isRunning(false)
{
}

App::~App()
{

}


bool App::Run()
{
    const size_t appMemorySize = 1024;

    auto memory = Sampler::Memory::Instance();
    if (!memory)
    {
        Logger::LogError( "Memory failed to intialise");
        return false;
    }

    Logger::LogInfo( "App intialised successfully");

    Logger::LogInfo( "Set isRunning to true.");
    m_isRunning = true;

    Logger::LogInfo("Beginning main loop.");
    while (m_isRunning)
    {
    }
    return true;
}
