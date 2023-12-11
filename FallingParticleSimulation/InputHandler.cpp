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

bool InputHandler::shouldQuit() {
	bool shouldQuit = false;

	SDL_Event e;

	//TODO: I hate this and would like to refactor in future
	while (SDL_PollEvent(&e) != 0) {
		// user requests to quit
		if (e.type == SDL_QUIT) {
			shouldQuit = true;
		}
	}

	if (!shouldQuit) {
		shouldQuit = isKeyPressed(SDL_SCANCODE_ESCAPE);
	}

	return shouldQuit;
}