#include "InputHandler.h"

InputHandler::InputHandler() {
	inputHandlerInit();
}

bool InputHandler::isKeyPressed(int key) {
	return (keyStates[key] == 1);
}

bool InputHandler::isMouseButtonPressed(int button) {
	return (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(button));
}

void InputHandler::getMousePosition(int* x, int* y) {
	SDL_GetMouseState(x, y);
}

void InputHandler::inputHandlerInit() {
	keyStates = SDL_GetKeyboardState(NULL);
}

void InputHandler::pollEvents(ParticleCreationFunction& func, bool& shouldQuit, int& radius) {
	SDL_Event e;

	//TODO: I hate this and would like to refactor in future
	while (SDL_PollEvent(&e) != 0) {
		// user requests to quit
		if (e.type == SDL_QUIT) {
			shouldQuit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case(SDLK_s):
					updateCurrentParticle(func, SAND);
					break;
				case(SDLK_w):
					updateCurrentParticle(func, WATER);
					break;
				case(SDLK_1):
					radius = 1;
					break;
				case(SDLK_2):
					radius = 10;
					break;
				case(SDLK_3):
					radius = 20;
					break;
				case(SDLK_4):
					radius = 30;
					break;
				case(SDLK_ESCAPE):
					shouldQuit = isKeyPressed(SDL_SCANCODE_ESCAPE);
					break;
			}
		}
	}
}