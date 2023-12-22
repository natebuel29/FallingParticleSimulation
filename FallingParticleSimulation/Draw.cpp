#include "Draw.h"

// Public
 void Draw::drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_Rect fillRect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &fillRect);
}