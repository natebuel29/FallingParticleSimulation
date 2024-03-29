#include "Simulation.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_impl_sdl2.h"
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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	bool showGUI = true;
	bool quit = false;

	int lastTime = SDL_GetTicks();
	int currentTime;
	int last_item = 0;

	while (!quit) {
		currentTime = SDL_GetTicks();

		//  // Start the Dear ImGui frame
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		if (currentTime - lastTime >= 1000) {
			lastTime = currentTime;
			std::string fpsString = "FPS COUNT: ";
			SDL_SetWindowTitle(window, fpsString.append(std::to_string(fpsCount)).c_str());
			fpsCount = 0;

		}
		inputHandler.pollEvents(quit, showGUI);

		//IMGUI logic
		if (showGUI)
		{
			ImGui::Begin("Controls", &showGUI);
			ImGui::Checkbox("SIM RUNNING", &simRunning);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

			const char* items[] = {"EMPTY", "OUTOFBOUNDS", "SAND", "WATER","SMOKE", "WOOD",  "ACID", "FIRE", "ICE"};
			static int item_current = 2;
			ImGui::Combo("PARTICLES", &item_current, items, IM_ARRAYSIZE(items));
			if (item_current != last_item) {
				updateCurrentParticle(createParticle, static_cast<ParticleType>(item_current));
				last_item = item_current;
			}
			static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
			static int slider_i = 10;
			ImGui::SliderInt("Brush Size", &slider_i, 1, 50, "%d", flags);
			radius = slider_i;
			ImGui::End();
		}

		if (simRunning) {
			step();
		}
		// Rendering
		render();

		fpsCount++;

		int frameTime = SDL_GetTicks() - currentTime;
		if (frameTime < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
		}

	}

}

// TODO: use input handle instead of passing around this gross bools
void Simulation::render() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0xFF);
	SDL_RenderClear(renderer);
	// Create surface to draw simulation on
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
	// Draw background on surface
	Draw::drawRect(surface, 0, 0, width, height, 100, 100, 100, 255);
	SDL_Texture* tex = NULL;
	for (int i = 0; i < gameTiles.getRowCount(); i++) {
		for (int j = 0; j < gameTiles.getColumnCount(); j++) {
			Particle* particle = gameTiles.getTileAddress(i, j, 0, 0);
			if (particle->type != ParticleType::EMPTY) {
				ParticleContext* context = ParticleContextManager::getInstance()->getParticleContext(particle->type);
				RGB* rgb = context->getRGBFromArray(particle->colorIndex);
				Draw::drawRect(surface, i * tileSize, j * tileSize, tileSize, tileSize, rgb->r, rgb->g, rgb->b,particle->alpha);
				particle->processed = false;
			}
		}
	}

	tex  = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, tex, NULL,NULL);
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(tex);
}


void Simulation::step() {
	bool isEvenFrame = fpsCount % 2 == 0;
	for (int j = isEvenFrame ? 0 : gameTiles.getColumnCount() - 1; isEvenFrame ? j < gameTiles.getColumnCount() : j >= 0;  isEvenFrame ? j++ : j--) {
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


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
				int roundX = Math::roundToNearestMultiple(x, tileSize) / tileSize;
				int roundY = Math::roundToNearestMultiple(j, tileSize) / tileSize;
				if (gameTiles.getTileAddress(roundX, roundY, 0, 0)->type == EMPTY) {
					gameTiles.setTile(roundX,roundY, 0, 0, createParticle());
				}			
			}
		}
	}
}


void Simulation::destroy() {


	// Cleanup
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// Will need to destroy renderer -> have a desctuctor for this?
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	window = NULL;
}

