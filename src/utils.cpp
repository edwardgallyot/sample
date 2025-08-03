#include "utils.hpp"

namespace utils 
{
    size_t gigabytes(size_t num) 
    {
        return megabytes(num) * 1024;
    }
    
    size_t megabytes(size_t num) 
    {
        return kilobytes(num) * 1024;
    }
    
    size_t kilobytes(size_t num) 
    {
        return num * 1024;
    }
} 