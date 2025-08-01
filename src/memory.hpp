#pragma once

#include <cstddef>

namespace Sampler
{
class Memory
{
public:
    static Memory* Instance();
    static void* Push(size_t size);
private:
    Memory();
    ~Memory();
    const size_t Size = 1024;
    static Memory* s_instance; 
    void *m_memory;
    size_t m_offset;
};
}