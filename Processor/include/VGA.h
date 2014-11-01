#pragma once

#include <SDL.h>

class Processor;

class VGA {
private:
	SDL_Window*  window;
	SDL_Renderer* renderer;

	Processor* proc;
	unsigned int pointer = 0x1000;
public:
	VGA(Processor* p) : proc(p) {}
	~VGA();

	void init();
	void render();

	void run();

};

