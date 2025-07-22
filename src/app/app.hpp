#include <atomic>
#include "memory/memory.hpp"

namespace Sampler
{
struct App 
{
    static bool Init(App* app);
    bool Run();
    std::atomic_bool isRunning = {false };
    Memory memory;
};
}
