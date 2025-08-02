#include <cstddef>
#include <cstdlib>
#include <sys/mman.h>
#include <unistd.h>

#include "memory.hpp"
#include "logger.hpp"
#include "types.hpp"

using namespace Smpl;

Memory::Memory(Logger& _logger)
    : offset(0),
      size(0),
      memory(nullptr),
      logger(_logger)
{
}

Memory::~Memory()
{
    if (this->memory != nullptr)
    {
        munmap(this->memory, this->size);
    }
}

bool Memory::Allocate(size_t size)
{
    if (this->memory != nullptr)
    {
        munmap(this->memory, this->size);
    }

    this->memory = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (this->memory == MAP_FAILED)
    {
        this->logger.LogError("Couldn't map memory of size: %u", size);
        return false;
    }

    this->size = size;
    return true;
}

void* Memory::Push(size_t size)
{
    size_t newOffset = this->offset + size;
    if (newOffset > this->size)
    {
        this->logger.LogError("Ran out of memory. Requested offset: %u, Memory size: %u", newOffset, this->size);
        return nullptr;
    }
    this->offset = newOffset;
    return (u8*)this->memory + this->offset;
}

