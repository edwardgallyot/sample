#pragma once

#include "types.hpp"

namespace smpl
{
    class logger;
    class memory;
}

namespace smpl
{
class terminal
{
public: 

    terminal();
    ~terminal();

    bool init(logger& logger, memory& memory, u32 num_commands);
    bool add_cmd(const char* name, const char* help, void (*callback)(const char*, void*), void* context);
    void welcome();
    bool handle_io_non_blocking();
private:

    void print_help();

    struct cmd
    {
        const char* name;
        const char* help;
        void (*callback)(const char*, void*);
        void* context;
    };

    cmd*    commands;
    size_t  commands_size;
    size_t  commands_count;

    char*  input_buffer;
    size_t input_count;
    size_t input_buffer_size;
};
}