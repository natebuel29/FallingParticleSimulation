#pragma once
#include <SDL.h>
#include "Renderer.h"

class Simulation
{
	public:
		Simulation(int width, int height);

		~Simulation();

		void simulate();

		void step();

	private:
		int width, height;
		
		SDL_Window* window;

		Renderer renderer;

		bool simulationInit();

		void destroy();
};

