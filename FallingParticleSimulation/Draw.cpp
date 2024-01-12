#include "Draw.h"

// Public
 void Draw::drawRect(SDL_Surface* surface, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_Rect fillRect = { x, y, w, h };
	SDL_FillRect(surface, &fillRect, SDL_MapRGBA(surface->format, r, g, b, a));

}