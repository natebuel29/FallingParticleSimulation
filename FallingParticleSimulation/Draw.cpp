#include "Draw.h"
#include <iostream>

// Public
 void Draw::drawRect(SDL_Renderer* renderer, int x, int y, int w, int h) {
	SDL_Rect fillRect = { x / 2, y / 2,  5, 5 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &fillRect);
}

