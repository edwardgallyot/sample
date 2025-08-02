#include "logger.hpp"
#include "memory.hpp"
#include "terminal.hpp"

namespace Sampler
{
class App 
{
public:
    App(Logger& logger);
    ~App();
    bool Run();
private:
    Logger& logger;
    Memory memory;
    Terminal terminal;
    bool isRunning;
};
}
