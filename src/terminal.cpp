
#include "terminal.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include <cstddef>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <termios.h>

using namespace smpl;

terminal::terminal()
    : 
    cmd_levels(),
    cmds(),
    input()
{
}

terminal::~terminal()
{
}

static void 
help_cmd(const char* s, void* ctx)
{
    auto* term = (terminal*)ctx;
    term->print_help();
}

bool 
terminal::init(logger& logger, utils::memory& memory)
{
    // Allocate command memory
    const size_t num_commands = 1024;
    cmd* data = memory.push<cmd>(num_commands);
    if (!data)
    {
        logger.log_error("Couldn't allocate commands buffer of size: %u", sizeof(cmd) * num_commands);
        return false;
    }
    this->cmds.assign(data, num_commands);

    const size_t max_cmd_levels = 256;
    cmd_level* cmd_level_data = memory.push<cmd_level>(max_cmd_levels);
    if (!cmd_level_data)
    {
        logger.log_error("Couldn't allocate command level buffer of size: %u", sizeof(cmd_level) * max_cmd_levels);
        return false;
    }
    this->cmd_levels.assign(cmd_level_data, max_cmd_levels);

    const size_t max_cmd_nodes = 256;
    utils::list<cmd_level>::node* cmd_node_data = memory.push<utils::list<cmd_level>::node>(max_cmd_nodes);
    if (!cmd_node_data)
    {
        logger.log_error("Couldn't allocate commands buffer of size: %u", sizeof(utils::list<cmd_level>::node) * max_cmd_nodes);
        return false;
    }
    this->cmd_nodes.assign(cmd_node_data, max_cmd_nodes);

    // Allocate input buffer memory
    const size_t input_buffer_size = 512;
    char* input_buffer = memory.push<char>(input_buffer_size);
    if (!input_buffer)
    {
        logger.log_error("Couldn't allocate input buffer of size: %u", input_buffer_size);
        return false;
    }
    this->input.assign(input_buffer, input_buffer_size);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    struct termios term;
    tcgetattr(fileno(stdin), &term);

    term.c_lflag &= ~(ECHO | ICANON);  
    tcsetattr(fileno(stdin), 0, &term);

    // Add the base command level
    auto* base_level = this->cmd_levels.push_empty();
    base_level->name = "base";
    base_level->help = "this is the base level at index 0";
    base_level->children = utils::list<cmd_level>();
    this->current_level = base_level;

    // Add our emptys, this helps with zii
    this->cmds.push_empty();
    this->cmd_nodes.push_empty();

    auto* help_level = this->add_cmd_level("HELP", "Prints out the help text", base_level);
    this->add_cmd_to_level(help_level, help_cmd, this);
    return true;
}

bool 
terminal::add_cmd_to_level(cmd_level* parent, void (*callback)(const char*, void*), void* context = nullptr)
{
    if (parent == nullptr)
    {
        parent = &this->cmd_levels.at(0);
    }

    parent->cmd_index = this->cmds.get_count();
    cmd cmd_to_push;
    cmd_to_push.callback = callback;
    cmd_to_push.context = context;
    this->cmds.push(cmd_to_push);
    return true;
}

terminal::cmd_level* 
terminal::add_cmd_level(const char* name, const char* help, cmd_level* parent)
{
    if (parent == nullptr)
    {
        parent = &this->cmd_levels.at(0);
    }

    auto* level = this->cmd_levels.push_empty();
    if (!level)
    {
        return nullptr;
    }
    level->name = name;
    level->help = help;
    level->children = utils::list<cmd_level>();

    auto* node  = this->cmd_nodes.push_empty();
    if (!node)
    {
        return nullptr;
    }

    node->data = level;
    node->next = nullptr;
    parent->children.add(node);
    return level;
}

void 
terminal::welcome()
{
    fputc('>', stdout);
}

bool 
terminal::handle_io_non_blocking()
{
    int c = getc(stdin);

    if (c == EOF) 
    {
        return true;
    }

    fputc(c, stdout);

    char* buf = this->input.raw();

    if (c == 8 || c == 127) // Backspace or Delete
    {
        if (auto _ = this->input.pop())
        {
            printf("\b \b"); 
        }
        return true;
    }

    if (c == '\n') 
    {
        size_t input_split = 0;
        size_t in = 0;
        for (in = 0; in < this->input.get_count(); ++in)
        {
            char input = buf[in];
            if (input == ' ' || input == 0)
            {
                break;
            }
        }
        input_split = in;

        bool found_match = false;
        bool has_input = this->input.get_count() > 0;
        if (!has_input)
        {
            fputc('>', stdout);
            return true;
        }

        auto* level = this->current_level->children.get_head();
        for (; level != nullptr; level = level->next)
        {
            if (!level->data)
            {
                continue;
            }

            found_match = strncasecmp(level->data->name, buf, input_split) == 0;
            if (!found_match)
            {
                continue;
            }


            auto& cmd = this->cmds.at(level->data->cmd_index);
            cmd.callback(
                buf + input_split,
                cmd.context
            );
            break;
        }

        if (has_input && !found_match)
        {
            printf("Command %.*s not found!\n", (int)input_split, buf);
        }

        this->input.zero();
        this->input.reset();

        fputc('>', stdout);
        return true;
    }

    bool pushed = this->input.push(c);
    if (!pushed)
    {
        printf("OVERFLOW\n");
        return false;
    }

    return true;
}


void 
terminal::print_help()
{
    auto* c = this->current_level->children.get_head();
    for (; c != nullptr; c = c->next)
    {
        if (!c->data)
        {
            continue;
        }
        printf("%s: %s\n", c->data->name, c->data->help);
    }
}
