#pragma once

#include <cstddef>
#include "logger.hpp"


namespace smpl
{

class memory
{
public:
    memory(logger& _log);
    ~memory();

    bool allocate(size_t size);

    void* push(size_t size);

    template<typename type>
    type* push(size_t count = 1);

private:
    void *memory_ptr;
    size_t offset;
    size_t size;
    logger& log;
};

template<typename type>
type* memory::push(size_t count)
{
    return reinterpret_cast<type*>(this->push(sizeof(type) * count));
}
}

