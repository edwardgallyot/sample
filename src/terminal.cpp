
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
    commands(nullptr),
    commands_size(0),
    commands_count(0),
    input_buffer(nullptr),
    input_count(0),
    input_buffer_size(0)
{
}

terminal::~terminal()
{
}


bool terminal::init(logger& logger, memory& memory, u32 num_commands)
{
    // Allocate command memory
    this->commands_size = num_commands * sizeof(cmd);
    this->commands = memory.push<cmd>(num_commands);
    if (!this->commands)
    {
        logger.log_error("Couldn't allocate commands buffer of size: %u", this->commands_size);
        this->commands_size = 0;
        return false;
    }

    // Allocate input buffer memory
    this->input_buffer_size = 512;
    this->input_buffer = memory.push<char>(this->input_buffer_size);
    if (!this->input_buffer)
    {
        logger.log_error("Couldn't allocate input buffer of size: %u", this->input_buffer_size);
        this->input_buffer_size = 0;
        return false;
    }

    memset(this->input_buffer, 0, this->input_buffer_size);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    struct termios term;
    tcgetattr(fileno(stdin), &term);

    term.c_lflag &= ~(ECHO | ICANON);  // Turn off echo and canonical mode
    tcsetattr(fileno(stdin), 0, &term);

    return true;
}

bool terminal::add_cmd(const char* name, const char* help, void (*callback)(const char*, void*), void* context = nullptr)
{
    if (this->commands_count >= this->commands_size)
    {
        return false;
    }
    this->commands[this->commands_count].name = name;
    this->commands[this->commands_count].help = help;
    this->commands[this->commands_count].callback = callback;
    this->commands[this->commands_count].context = context;
    this->commands_count++;
    return true;
}

void terminal::welcome()
{
    fputc('>', stdout);
}

bool terminal::handle_io_non_blocking()
{
    int c = getc(stdin);

    if (c == EOF) 
    {
        return true;
    }

    fputc(c, stdout);

    char* buf = this->input_buffer;

    if (c == '\n') 
    {
        size_t input_split = 0;
        {
            size_t in = 0;
            for (in = 0; in < this->input_count; ++in)
            {
                char input = buf[in];
                if (input == ' ' || input == 0)
                {
                    break;
                }
            }
            input_split = in;
        }

        bool found_match = false;
        bool has_input = this->input_count > 0;
        if (has_input)
        {
            for (size_t cmd = 0; cmd < this->commands_count; ++cmd)
            {
                auto& command = this->commands[cmd];
            
                found_match = strncasecmp(command.name, buf, input_split) == 0;
                if (found_match)
                {
                    command.callback(buf + input_split, command.context);
                    break;
                }
            }
        }


        if (has_input && !found_match)
        {
            if (strncasecmp("help", this->input_buffer, input_split) == 0)
            {
                printf("\n");
                for (size_t cmd = 0; cmd < this->commands_count; ++cmd)
                {
                    auto& command = this->commands[cmd];
                    printf("%s: %s\n", command.name, command.help);
                }
            }
            else 
            {
                printf("Command %.*s not found!\n", input_split, buf);
            }
        }

        memset(buf, 0, this->input_buffer_size);
        this->input_count = 0;
        fputc('>', stdout);
        return true;
    }

    if (input_count >= input_buffer_size)
    {
        printf("OVERFLOW\n");
        return false;
    }
   
    this->input_buffer[this->input_count] = c; 
    this->input_count++;

    return true;
}
