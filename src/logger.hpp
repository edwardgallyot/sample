#pragma once

#include <cstdio>

namespace smpl
{
class logger
{
public:
    logger(const char* _name);
    enum class level
    {
        info,
        warning,
        error,
        critical,
    };

    void log_info(const char* message, ...);
    void log_warning(const char* message, ...);
    void log_error(const char* message, ...);
    void log_critical(const char* message, ...);
private:
    const char* get_prefix_for_level(level level);
    void log(level level, const char* message, va_list args);
    const char* name;
    FILE* file;
};
}
