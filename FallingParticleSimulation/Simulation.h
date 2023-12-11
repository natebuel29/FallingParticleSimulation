#pragma once
#include <SDL.h>
#include <string>
#include "GameTiles.h"
#include "Math.h"
#include "Logger.h"
#include "InputHandler.h"

class Simulation
{
	public:

		Simulation(int width, int height);

		~Simulation();

		void render();

		void simulate();

		void step(bool* quit);


	private:
		int width, height;
	
		const int tileSize = 5;
		
		GameTiles gameTiles;

		SDL_Window* window;

		SDL_Renderer* renderer;

		InputHandler inputHandler;

		bool simulationInit();

		void destroy();
};