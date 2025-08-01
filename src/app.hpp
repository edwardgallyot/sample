#include <atomic>
#include "memory.hpp"
#include "logger.hpp"

namespace Sampler
{
class App 
{
public:
    App();
    ~App();
    bool Run();
private:
    bool m_isRunning;
};
}
