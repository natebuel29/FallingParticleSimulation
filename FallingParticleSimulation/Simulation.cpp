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
	//	ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	bool show_another_window = true;

	bool quit = false;

	int lastTime = SDL_GetTicks();
	int currentTime;
	bool showDemoWindow = true;

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
		step();
		// draw to screen
		//https://stackoverflow.com/questions/72645989/rectangle-to-texture-in-sdl2-c - draw to surface -> texture? will this resolve
// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
		inputHandler.pollEvents(createParticle, quit, radius);

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

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect background;
	background.x =0;
	background.y = 0;
	background.w = width;
	background.h = height;
	SDL_FillRect(surface, &background, SDL_MapRGB(surface->format, 100, 100, 100));

	SDL_RenderClear(renderer);
	SDL_Texture* tex = NULL;
	for (int i = 0; i < gameTiles.getRowCount(); i++) {
		for (int j = 0; j < gameTiles.getColumnCount(); j++) {
			Particle* particle = gameTiles.getTileAddress(i, j, 0, 0);
			if (particle->type != ParticleType::EMPTY) {
				ParticleContext* context = ParticleContextManager::getInstance()->getParticleContext(particle->type);
				RGB* rgb = context->getRGBFromArray(particle->colorIndex);
				//Draw::drawRect(renderer, i * tileSize, j * tileSize, tileSize, tileSize, rgb->r, rgb->g, rgb->b,particle->alpha);
				particle->processed = false;
				SDL_Rect rect;
				rect.x = i* tileSize;
				rect.y = j* tileSize;
				rect.w = tileSize;
				rect.h = 5;
				SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, rgb->r, rgb->g, rgb->b));
			}
		}
	}

	tex  = SDL_CreateTextureFromSurface(renderer, surface);
	//check if texture was created
	if (tex == NULL) {
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, tex, NULL,NULL);

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(tex);
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
				gameTiles.setTile(Math::roundToNearestMultiple(x, tileSize) / tileSize, Math::roundToNearestMultiple(j, tileSize) / tileSize, 0, 0, createParticle());
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

