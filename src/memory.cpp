#include <cstddef>
#include <cstdlib>
#include <sys/mman.h>
#include <unistd.h>

#include "memory.hpp"
#include "logger.hpp"
#include "types.hpp"

using namespace smpl;

memory::memory(logger& _logger)
    : offset(0),
      size(0),
      memory_ptr(nullptr),
      log(_logger)
{
}

memory::~memory()
{
    if (this->memory_ptr != nullptr)
    {
        munmap(this->memory_ptr, this->size);
    }
}

bool memory::allocate(size_t size)
{
    if (this->memory_ptr != nullptr)
    {
        munmap(this->memory_ptr, this->size);
    }

    this->memory_ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (this->memory_ptr == MAP_FAILED)
    {
        this->log.log_error("Couldn't map memory of size: %u", size);
        return false;
    }

    this->size = size;
    return true;
}

void* memory::push(size_t size)
{
    size_t new_offset = this->offset + size;
    if (new_offset > this->size)
    {
        this->log.log_error("Ran out of memory. Requested offset: %u, Memory size: %u", new_offset, this->size);
        return nullptr;
    }
    this->offset = new_offset;
    return (u8*)this->memory_ptr + this->offset;
}

