#include "app/app.hpp"
#include "memory/memory.hpp"

int main(int argc, char** argv)
{
    Sampler::App app;
    bool isAppInitialised = Sampler::App::Init(&app);
    if (!isAppInitialised)
    {
        return -1;
    }
    app.Run();
    return 0;
}
