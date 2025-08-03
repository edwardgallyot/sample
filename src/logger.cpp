#include "logger.hpp"
#include "memory.hpp"
#include <cstdarg>
#include <cstdio>
#include <cwchar>

using namespace smpl;


logger::logger(const char* _name)
: name(_name),
  file(nullptr)
{
}

const char* logger::get_prefix_for_level(level l)
{
    switch (l)
    {
    case level::info: return "INFO";
    case level::warning: return "WARNING";
    case level::error: return "ERROR";
    case level::critical: return "CRITICAL";
    default: return "UNKNOWN";
    }
}

void logger::log(level l, const char* message, va_list args)
{
    std::printf("[%s] %s: ", this->name, get_prefix_for_level(l));
    std::vprintf(message, args);
    std::printf("\n");
}

void logger::log_info(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    log(level::info, message, args);
    va_end(args);
}

void logger::log_warning(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    log(level::warning, message, args);
    va_end(args);
}

void logger::log_error(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    log(level::error, message, args);
    va_end(args);
}

void logger::log_critical(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    log(level::critical, message, args);
    va_end(args);
}
