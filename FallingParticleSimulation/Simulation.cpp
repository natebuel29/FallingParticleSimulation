#include "Simulation.h"
#include <iostream>
#include "Draw.h"
#include "Logger.h"
#include <string>

// PUBLIC

Simulation::Simulation(int w, int h):width(w), height(h) {
	this->width = w;
	this->height = h;
	simulationInit();
}

Simulation::~Simulation() {
	destroy();
}

void Simulation::simulate() {

	bool quit = false;
	bool mouseButtonPressed = false;
	SDL_Event e;
	int x = 0, y = 0;

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			// user requests to quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				Logger::getInstance()->info("yo button mouse button is down");
				mouseButtonPressed = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				Logger::getInstance()->info("yo button mouse button is up");
				mouseButtonPressed = false;
				x = 0;
				y = 0;
			}
		}


		//Clear screen
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xFF);
		SDL_RenderClear(renderer);
		
		if (mouseButtonPressed) {
			SDL_GetMouseState(&x, &y);
			x = Math::roundToNearestMultiple(x, 5);
			y = Math::roundToNearestMultiple(y, 5);
			gameTiles.setTile(x / 5, y / 5, 0, 0, createSandParticle());
		}

		for (int i = 0; i < gameTiles.getRowCount(); i++) {
			for (int j = 0; j < gameTiles.getColumnCount(); j++) {
				if (gameTiles.getTile(i, j, 0, 0).type != ParticleType::EMPTY) {
					Draw::drawRect(renderer, i * 5, j * 5, 5, 5);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

}

void Simulation::render() {

}

void Simulation::step() {
	
}


// PRIVATE

bool Simulation::simulationInit() {
	window = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::string errorMessage = "Error while initializing SDL2: ";
		Logger::getInstance()->error(errorMessage.append(SDL_GetError()));
		return false;
	}

	window = SDL_CreateWindow
	(
		"Falling Particle Simulation", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr) {
		std::string errorMessage = "Error while creating window: ";
		Logger::getInstance()->error(errorMessage.append(SDL_GetError()));
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::string errorMessage = "Renderer could not be created! SDL Error: ";
		Logger::getInstance()->error(errorMessage.append(SDL_GetError()));
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	gameTiles = GameTiles(this->width / 5, this->height / 5);

	return true;
}

void Simulation::destroy() {
	// Will need to destroy renderer -> have a desctuctor for this?
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	window = NULL;
}

