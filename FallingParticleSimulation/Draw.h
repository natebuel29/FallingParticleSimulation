#pragma once
#include <SDL.h>
#include <iostream>
#include "Math.h"
class Draw
{

public:
	static void drawRect(SDL_Surface* surface, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

