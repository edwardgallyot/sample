#include "utils.hpp"

namespace Utils 
{
    size_t Gigabytes(size_t num) 
    {
        return Megabytes(num) * 1024;
    }
    
    size_t Megabytes(size_t num) 
    {
        return Kilobytes(num) * 1024;
    }
    
    size_t Kilobytes(size_t num) 
    {
        return num * 1024;
    }
} 