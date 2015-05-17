#pragma once

#include <SDL.h>

class Processor;

class VGA {
private:
	SDL_Window*  window;
	SDL_Renderer* renderer;
	bool running;

	Processor* proc;
	unsigned int pointer = 0x1000;
public:
	VGA(Processor* p) : proc(p), running(true) {}
	~VGA();

	void init();
	void render();

	void run();

	void stop();

};

