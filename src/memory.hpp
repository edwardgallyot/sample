#pragma once

#include <cstddef>


namespace utils
{

class memory
{
public:
    memory();
    ~memory();

    bool allocate(size_t size);

    void* push(size_t size);

    template<typename type>
    type* push(size_t count);

private:
    void *memory_ptr;
    size_t offset;
    size_t size;
};

template<typename type>
type* memory::push(size_t count)
{
    return reinterpret_cast<type*>(this->push(sizeof(type) * count));
}
}

