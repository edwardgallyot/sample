#include <cstdlib>

#include "memory.hpp"

using namespace Sampler;

Memory* Memory::s_instance = nullptr;

Memory::Memory()
    : m_offset(0)
{
    m_memory = std::malloc(Memory::Size);
}

Memory::~Memory()
{
}

void* Memory::Push(size_t size)
{
    return std::malloc(size);
}

Memory* Memory::Instance()
{
    if (s_instance == nullptr)
    {
        static Memory s_memory = Memory();
        s_instance = &s_memory;
    }
    return s_instance;
}
