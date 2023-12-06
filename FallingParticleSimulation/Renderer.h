#pragma once
#include <SDL.h>

class Renderer
{

public:
	Renderer();

	Renderer(SDL_Window* window);

	~Renderer();


	void drawRect(int x, int y, int w, int h);

	void clearScreen();
	
	void renderPresent();

private:
	SDL_Renderer* renderer;

	void destroy();
};

