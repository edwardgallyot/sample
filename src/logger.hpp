#pragma once

#include <cstdio>

namespace Sampler
{
class Logger
{
public:
    enum class Level
    {
        Info,
        Warning,
        Error,
        Critical,
    };

    static void Init(const char* name, FILE* file = nullptr);
    static void LogInfo(const char* message, ...);
    static void LogWarning(const char* message, ...);
    static void LogError(const char* message, ...);
    static void LogCritical(const char* message, ...);
    void* operator new(size_t size);
private:
    Logger(const char* name, FILE* file = nullptr);
    static const char* GetPrefixForLevel(Level level);
    static void Log(Level level, const char* message, va_list args);
    
    const char* m_name = nullptr;
    FILE* m_file = nullptr;
    static Logger* s_instance;
};
}
