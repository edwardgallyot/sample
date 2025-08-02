#pragma once

#include <cstdio>

namespace Smpl
{
class Logger
{
public:
    Logger(const char* _name);
    enum class Level
    {
        Info,
        Warning,
        Error,
        Critical,
    };

    void LogInfo(const char* message, ...);
    void LogWarning(const char* message, ...);
    void LogError(const char* message, ...);
    void LogCritical(const char* message, ...);
private:
    const char* GetPrefixForLevel(Level level);
    void Log(Level level, const char* message, va_list args);
    const char* name;
    FILE* file;
};
}
