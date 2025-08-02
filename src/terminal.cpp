
#include "terminal.hpp"

using namespace Sampler;

Terminal::Terminal()
    : 
    commandTreeNodes(nullptr),
    commandTreeNodesSize(0)
{
}

Terminal::~Terminal()
{
}


bool Terminal::Allocate(Memory& memory, u32 numCommands)
{
    this->commandTreeNodes = memory.Push<CmdNode>(numCommands);
    if (!this->commandTreeNodes)
    {
        return false;
    }
    return true;
}