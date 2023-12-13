#include "Simulation.h"

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

	while (!quit) {

		step(&quit);
		// draw to screen
		render();

		quit = inputHandler.shouldQuit();
	}

}

// TODO: use input handle instead of passing around this gross bools
void Simulation::render() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xFF);
	SDL_RenderClear(renderer);
	int x = 0, y = 0;

	if (inputHandler.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
		inputHandler.getMousePosition(&x, &y);
		x = Math::roundToNearestMultiple(x, 5);
		y = Math::roundToNearestMultiple(y, 5);
		gameTiles.setTile(x / 5, y / 5, 0, 0, createSandParticle());
	}

	for (int i = 0; i < gameTiles.getRowCount(); i++) {
		for (int j = 0; j < gameTiles.getColumnCount(); j++) {
			if (gameTiles.getTile(i, j, 0, 0).type != ParticleType::EMPTY) {
				RGB rgb = getRGBFromColor(gameTiles.getTile(i, j, 0, 0).color);
				Draw::drawRect(renderer, i * 5, j * 5, 5, 5,rgb.r,rgb.g,rgb.b,rgb.a);
			}
		}
	}
	SDL_RenderPresent(renderer);

}

// TODO: use input handle instead of passing around this gross bools
void Simulation::step(bool* quit) {

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

	inputHandler = InputHandler();

	return true;
}

void Simulation::destroy() {
	// Will need to destroy renderer -> have a desctuctor for this?
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	window = NULL;
}

