#pragma once
#include <SDL.h>
#include "Particles.h"

class InputHandler
{
	public:
		InputHandler();

		bool isKeyPressed(int key);
		
		bool isMouseButtonPressed(int button);

		void getMousePosition(int* x, int* y);

		// not a fan of this and would like to refactor in future
		void pollEvents(bool& shouldQuit, bool& showGUI);		
	private:
		void inputHandlerInit();
		const Uint8* keyStates = nullptr;
};

