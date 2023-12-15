#pragma once
#include <SDL.h>
#include "GameTiles.h"
#include "Math.h"
#include "InputHandler.h"
#include "Draw.h"
#include "Logger.h"
#include "Colors.h"
#include "ParticleContextManager.h"
#include "ParticleHandler.h"
#include <string>
#include <iostream>



class Simulation
{
	public:

		Simulation(int width, int height);

		~Simulation();

		void render();

		void simulate();

		void step();


	private:
		int width, height;
	
		const int tileSize = 5;
		
		GameTiles gameTiles;

		SDL_Window* window;

		SDL_Renderer* renderer;

		InputHandler inputHandler;
		
		//TODO: delete this ?
		ParticleContextManager pcManager;

		ParticleHandler parHandler;

		bool simulationInit();

		void destroy();
};