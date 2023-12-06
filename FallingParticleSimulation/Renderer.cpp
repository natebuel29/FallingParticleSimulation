#include "Renderer.h"
#include <iostream>

// Public
// Need this because i  was getting a "no appropriate default constructor available" error. Need to figure out a way to not need this
Renderer::Renderer() {
	renderer = NULL;
}

Renderer::Renderer(SDL_Window* window) {
	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

}


Renderer::~Renderer() {
	destroy();
}

void Renderer::drawRect(int x, int y, int w, int h) {
	SDL_Rect fillRect = { x / 4, y / 4, w / 2, h / 2 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &fillRect);
}

void Renderer::renderPresent() {
	SDL_RenderPresent(renderer);
}

void Renderer::clearScreen() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xFF);
	SDL_RenderClear(renderer);
}

// Private

void Renderer::destroy() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}

