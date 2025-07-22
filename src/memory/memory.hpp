#pragma once
#include <cstddef>

namespace Sampler
{
struct Memory
{
    static bool Init(Memory* memory, size_t size);
    void *memory = nullptr;
    size_t size = 0;
};
}