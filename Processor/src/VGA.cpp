#include "..\include\VGA.h"

#include <SDL.h>
#include <SDL_render.h>
#include <Processor.h>

VGA::~VGA() {}

void VGA::run() {
	init();
	while(running) {
		SDL_PollEvent(NULL);
		render();
		SDL_Delay(1000/60);
	}
}

void VGA::stop() {
	running = false;
}

void VGA::render() {
	int* bmp = (int*) (proc->ram.get() + pointer);
	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(bmp, 800, 600, 32, 800*4, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_Rect whole = {0,0,800,600};
	SDL_RenderCopy(renderer, text, &whole, &whole);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(text);

	SDL_UpdateWindowSurface(window);
}

void VGA::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("VGA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(renderer);
	SDL_RenderDrawLine(renderer, 0,0,800,600);
}