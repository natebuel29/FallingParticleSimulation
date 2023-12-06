#include "Simulation.h"
#include <iostream>
#include "Renderer.h"

// PUBLIC

Simulation::Simulation(int width, int height) {
	this->width = width;
	this->height = height;
	simulationInit();
}

Simulation::~Simulation() {
	destroy();
}

void Simulation::simulate() {

	bool quit = false;
	SDL_Event e;

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			// user requests to quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		renderer.clearScreen();
		renderer.drawRect(width,height,width,height);
		renderer.renderPresent();
	}
}

void Simulation::step() {
	
}


// PRIVATE

bool Simulation::simulationInit() {
	window = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error while initializing SDL2: %s\n", SDL_GetError());
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
		printf("Error while creating window: %s\n", SDL_GetError());
		return false;
	}

	renderer = Renderer(window);

	return true;
}

void Simulation::destroy() {
	// Will need to destroy renderer -> have a desctuctor for this?
	SDL_DestroyWindow(window);
	SDL_Quit();

	window = NULL;
}

