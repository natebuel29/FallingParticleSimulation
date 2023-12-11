#pragma once
#include <SDL.h>
class InputHandler
{
	public:
		InputHandler();

		bool isKeyPressed(int key);
		
		bool isMouseButtonPressed(int button);

		void getMousePosition(int* x, int* y);

		bool shouldQuit();
		
	private:
		void inputHandlerInit();
		const Uint8* keyStates = nullptr;
};

