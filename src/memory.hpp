#pragma once

#include "logger.hpp"
#include <cstddef>

namespace Sampler
{
class Memory
{
public:
    Memory(Logger& _logger);
    ~Memory();

    bool Allocate(size_t size);

    void* Push(size_t size);

    template<typename T>
    T* Push(size_t count = 1);

private:
    static Memory* s_instance; 
    void *memory;
    size_t offset;
    size_t size;
    Logger& logger;
};

template<typename T>
T* Memory::Push(size_t count)
{
    return reinterpret_cast<T*>(this->Push(sizeof(T) * count));
}

}

