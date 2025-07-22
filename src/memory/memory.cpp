#include "memory/memory.hpp"
#include <cstdlib>

using namespace Sampler;

bool Memory::Init(Memory* memory, size_t size)
{
    memory->size = size;
    void* alloced = malloc(size);
    if (!alloced)
    {
        return false;
    }
    memory->memory = alloced;
    return true;
}
