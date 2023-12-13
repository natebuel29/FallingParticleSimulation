#pragma once
#include <SDL.h>

class Draw
{

public:

	static void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

};

