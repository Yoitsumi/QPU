#pragma once

#include <SDL.h>

#include "Device.h"

class VGADevice : public Device {
public:
	VGADevice();
	~VGADevice();

private:
	SDL_Renderer* renderer;

};

