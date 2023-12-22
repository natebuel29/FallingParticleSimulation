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

		int radius = 10;
		
		GameTiles gameTiles;

		SDL_Window* window;

		SDL_Renderer* renderer;

		InputHandler inputHandler;

		ParticleHandler parHandler;

		ParticleCreationFunction createParticle;

		int fpsCount = 0;

		void fillCircle(int centerX, int centerY, int radius);

		bool simulationInit();

		void destroy();
};