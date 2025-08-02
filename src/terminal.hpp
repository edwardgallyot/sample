#include "memory.hpp"
#include "types.hpp"

namespace Sampler
{
class Terminal
{
public: 
    struct Cmd
    {
        const char* name;
        const char* help;
        virtual void command() = 0;
    };

    struct CmdNode
    {
        Cmd* cmd;
        CmdNode* child;
        size_t childCount;
    };

    Terminal();
    ~Terminal();

    bool Allocate(Memory& memory, u32 numCommands);
    bool AddCmd(Cmd* cmd, CmdNode* level);
private:
    CmdNode*    commandTreeNodes;
    size_t      commandTreeNodesSize;
};
}