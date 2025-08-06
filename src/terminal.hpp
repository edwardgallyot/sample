#pragma once

#include "logger.hpp"
#include "buffer.hpp"
#include "memory.hpp"
#include "list.hpp"

namespace smpl
{
class terminal
{
public: 

    terminal();
    ~terminal();


    struct cmd_level
    {
        const char* name;
        const char* help;
        utils::list<cmd_level> children;
        size_t cmd_index;
    };

    bool init(logger& logger, utils::memory& memory);

    inline constexpr cmd_level* get_base_level() { return &cmd_levels.at(0); }
    cmd_level* add_cmd_level(const char* name, const char* help, cmd_level* parent = nullptr);
    bool add_cmd_to_level(cmd_level* level, void (*callback)(const char*, void*), void* context);

    void welcome();
    bool handle_io_non_blocking();
    void print_help();

private:

    struct cmd
    {
        void (*callback)(const char*, void*);
        void* context;
    };

    cmd_level* current_level;
    utils::buffer<cmd_level> cmd_levels;
    utils::buffer<utils::list<cmd_level>::node> cmd_nodes;
    utils::buffer<cmd> cmds;
    utils::buffer<char> input;
};
}
