#include "InputHandler.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"

InputHandler::InputHandler() {
	inputHandlerInit();
}

bool InputHandler::isKeyPressed(int key) {
	return (keyStates[key] == 1);
}

bool InputHandler::isMouseButtonPressed(int button) {
	ImGuiIO& io = ImGui::GetIO();
	if (!io.WantCaptureMouse) {
		return (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(button));
	}
	else {
		return false;
	}
}

void InputHandler::getMousePosition(int* x, int* y) {
	SDL_GetMouseState(x, y);
}

void InputHandler::inputHandlerInit() {
	keyStates = SDL_GetKeyboardState(NULL);
}

void InputHandler::pollEvents(bool& shouldQuit, bool& showGUI) {
	SDL_Event e;

	//TODO: I hate this and would like to refactor in future
	while (SDL_PollEvent(&e) != 0) {
		// user requests to quit
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT) {
			shouldQuit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case(SDLK_d):
					showGUI = !showGUI;
					break;
				case(SDLK_ESCAPE):
					shouldQuit = isKeyPressed(SDL_SCANCODE_ESCAPE);
					break;
			}
		}
	}
}