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

	int lastTime = SDL_GetTicks();
	int currentTime;

	while (!quit) {
		inputHandler.pollEvents(createParticle, quit, radius);
		currentTime = SDL_GetTicks();

		if (currentTime - lastTime >= 1000) {
			lastTime = currentTime;
			std::string fpsString = "FPS COUNT: ";
			SDL_SetWindowTitle(window, fpsString.append(std::to_string(fpsCount)).c_str());
			fpsCount = 0;

		}
		step();
		// draw to screen
		render();

		fpsCount++;

		int frameTime = SDL_GetTicks() - currentTime;
		if (frameTime < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
		}

	//	resetParticles();

	}

}

// TODO: use input handle instead of passing around this gross bools
void Simulation::render() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xFF);
	SDL_RenderClear(renderer);

	for (int i = 0; i < gameTiles.getRowCount(); i++) {
		for (int j = 0; j < gameTiles.getColumnCount(); j++) {
			Particle* particle = gameTiles.getTileAddress(i, j, 0, 0);
			if (particle->type != ParticleType::EMPTY) {
				ParticleContext* context = ParticleContextManager::getInstance()->getParticleContext(particle->type);
				RGB* rgb = context->getRGBFromArray(particle->colorIndex);
				Draw::drawRect(renderer, i * tileSize, j * tileSize, tileSize, tileSize, rgb->r, rgb->g, rgb->b, rgb->a);
				particle->processed = false;
			}
		}
	}

	SDL_RenderPresent(renderer);
}

// TODO: use input handle instead of passing around this gross bools
void Simulation::step() {
	bool isEvenFrame = fpsCount % 2 == 0;
	for (int j = 0; j < gameTiles.getColumnCount(); j++) {
		for (int i =  isEvenFrame ? 0 : gameTiles.getRowCount()-1; isEvenFrame ? i < gameTiles.getRowCount() : i >= 0; isEvenFrame? i++ : i--) {
			Particle* particle = gameTiles.getTileAddress(i, j, 0, 0);
			if (particle->type != EMPTY && particle->processed == false) {
				parHandler.handleParticle(&gameTiles, i, j,fpsCount);
			}
		}
	}

	
	//Check for user input and create Sand Particle at mouse position
	int x = 0, y = 0;
	if (inputHandler.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
		inputHandler.getMousePosition(&x, &y);
		fillCircle(x, y, radius);
	}
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
	// use delta time for loop instead of vsync
	renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::string errorMessage = "Renderer could not be created! SDL Error: ";
		Logger::getInstance()->error(errorMessage.append(SDL_GetError()));
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	gameTiles = GameTiles(this->width / tileSize, this->height / tileSize);

	inputHandler = InputHandler();
	
	parHandler = ParticleHandler();

	updateCurrentParticle(createParticle, SAND);

	return true;
}

//TODO: replace this with mid point circle algorithm?
void Simulation::fillCircle(int centerX, int centerY, int radius) {
	centerX = Math::roundToNearestMultiple(centerX, tileSize);
	centerY = Math::roundToNearestMultiple(centerY, tileSize);

	if (radius == 1) {
		gameTiles.setTile(centerX / tileSize, centerY / tileSize, 0, 0, createParticle());
	}
	else {
		//how inefficient will this be?
		for (int i = 1; i < 36; i++) {
			double radians = i * tileSize * M_PI / 180;
			int x = centerX + radius * (cos(radians));
			int y = centerY + radius * (sin(radians));
			int minus_y = centerY - radius * (sin(radians));

			for (int j = minus_y; j < y; j++) {
				gameTiles.setTile(Math::roundToNearestMultiple(x, tileSize) / tileSize, Math::roundToNearestMultiple(j, tileSize) / tileSize, 0, 0, createParticle());
			}
		}
	}
}


void Simulation::destroy() {
	// Will need to destroy renderer -> have a desctuctor for this?
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	window = NULL;
}

