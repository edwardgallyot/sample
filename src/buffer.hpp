
#include <cstddef>
#include <cstring>
#include <utility>

namespace utils
{

template <typename type>
class buffer
{
public:    
    buffer();

    inline constexpr void assign(type* data, size_t size);
    inline constexpr bool push(type& data);
    inline constexpr bool push(type&& data);
    inline constexpr type* push_empty();
    inline constexpr type* pop();
    inline constexpr size_t get_count() { return this->count; }
    inline constexpr size_t get_size() { return this->size; }
    inline constexpr type& at(size_t i) { return this->data[i]; }
    inline constexpr void reset() { this->count = 0; }
    inline constexpr type* raw() { return this->data; }
    inline constexpr void zero() { memset(data, 0, size * sizeof(type)); }
private:
    type* data;
    size_t count;
    size_t size;
};

template <typename type>
buffer<type>::buffer()
    : 
    data(nullptr),
    count(0),
    size(0)
{
}

template <typename type>
inline constexpr bool 
buffer<type>::push(type& to_push)
{
    if (count >= size) return false;
    this->data[this->count] = to_push;
    this->count++;
    return true;
}

template <typename type>
inline constexpr bool 
buffer<type>::push(type&& to_push)
{
    if (this->count >= this->size) return false;
    this->data[this->count] = std::move(to_push);
    this->count++;
    return true;
}


template <typename type>
inline constexpr type* 
buffer<type>::push_empty()
{
    if (this->count >= this->size) return nullptr;
    type* to_return = &this->data[this->count];
    this->count++;
    return to_return;
}

template <typename type>
inline constexpr type* 
buffer<type>::pop()
{
    if (count == 0)
    {
        return nullptr;
    }
    type& to_return = this->data[this->count];
    this->count--;
    return &to_return;
}

template <typename type>
inline constexpr void 
buffer<type>::assign(type* data, size_t size)
{
    this->data = data;
    this->size = size;
}

}

