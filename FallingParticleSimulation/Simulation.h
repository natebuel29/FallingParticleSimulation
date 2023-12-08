#pragma once
#include <SDL.h>
#include "GameTiles.h"

class Simulation
{
	public:

		Simulation(int width, int height);

		~Simulation();

		void simulate();

		void step();


	private:
		int width, height;
	
		const int tileSize = 5;
		
		GameTiles gameTiles;

		SDL_Window* window;

		SDL_Renderer* renderer;

		bool simulationInit();

		void destroy();
};