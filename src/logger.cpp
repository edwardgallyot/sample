#include "logger.hpp"
#include "memory.hpp"
#include <cstdarg>
#include <cstdio>
#include <cwchar>

using namespace Sampler;


Logger::Logger(const char* _name)
: name(_name),
  file(nullptr)
{
}

const char* Logger::GetPrefixForLevel(Level level)
{
    switch (level)
    {
    case Level::Info: return "INFO";
    case Level::Warning: return "WARNING";
    case Level::Error: return "ERROR";
    case Level::Critical: return "CRITICAL";
    default: return "UNKNOWN";
    }
}

void Logger::Log(Level level, const char* message, va_list args)
{
    std::printf("[%s] %s: ", this->name, GetPrefixForLevel(level));
    std::vprintf(message, args);
    std::printf("\n");
}

void Logger::LogInfo(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Log(Level::Info, message, args);
    va_end(args);
}

void Logger::LogWarning(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Log(Level::Warning, message, args);
    va_end(args);
}

void Logger::LogError(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Log(Level::Error, message, args);
    va_end(args);
}

void Logger::LogCritical(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Log(Level::Critical, message, args);
    va_end(args);
}
