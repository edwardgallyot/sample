#include <cstdio>
#include "alsa.hpp"
#include "logger.hpp"
#include <alsa/asoundlib.h>

using namespace smpl;

alsa_io::alsa_io(logger& _log)
    : log(_log)
{

}

alsa_io::~alsa_io()
{

}

static void enumerate_devices(const char* s, void* context)
{
    // Yoinked form here:
    // https://github.com/OpenPixelSystems/c-alsa-examples/blob/master/utils/list-devices.c
    // Not under a license but assuming MIT?
    alsa_io* alsa = reinterpret_cast<alsa_io*>(context);

    void** hints;
    int err = snd_device_name_hint(-1, "pcm", (void***)&hints);

    if (err != 0) 
    {
        printf("Error getting device hints (%d)", err);
    }

    char **n = (char **)hints;
	while (*n != NULL) {
		char *name = snd_device_name_get_hint(*n, "NAME");
		if (name != NULL) {
			printf("%s\n", name);
			free(name);
		}
		n++;
	}
	snd_device_name_free_hint(hints);

}

bool alsa_io::init(memory& memory, terminal& term)
{
    term.add_cmd("ALSA", "Alsa IO commands", enumerate_devices, this);

    return true;
}
