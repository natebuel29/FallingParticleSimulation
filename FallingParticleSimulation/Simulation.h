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
	
		const int tileSize = 4;

		int radius = 10;
		
		GameTiles gameTiles;

		SDL_Window* window;

		SDL_Renderer* renderer;

		InputHandler inputHandler;

		ParticleHandler parHandler;

		ParticleCreationFunction createParticle;

		int fpsCount = 0;

		const int SCREEN_FPS = 60;
		
		const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

		void fillCircle(int centerX, int centerY, int radius);

		bool simulationInit();

		void destroy();
};