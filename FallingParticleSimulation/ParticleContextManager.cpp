#include "ParticleContextManager.h"

// Public
ParticleContextManager* ParticleContextManager::instance = nullptr;

ParticleContextManager* ParticleContextManager::getInstance() {
	if (instance == nullptr) {
		instance = new ParticleContextManager();
	}

	return instance;
}
ParticleContext* ParticleContextManager::getParticleContext(ParticleType particle) {
	ParticleContext* particleContext = nullptr;

	switch (particle) {
		case ParticleType::SAND:
			particleContext = &sand;
			break;
		case ParticleType::WATER:
			particleContext = &water;
			break;
		case ParticleType::WOOD:
			particleContext = &wood;
			break;
		case ParticleType::SMOKE:
			particleContext = &smoke;
			break;
	}
	if (particleContext == nullptr) {
		Logger::getInstance()->error("AHHH NO PARTICLE CONTEXT SOMETHINGS GONE HORRIBLY WRONG");
	}
	return particleContext;
}

ParticleContextManager::ParticleContextManager() {
	std::array<RGB, 5> sandColors = { RGB{ 246,215,176,1 }, RGB{242,210,169,1}, RGB{236,204,162,1}, RGB{231,196,150,1}, RGB{225,191,146,1} };
	sand = ParticleContext(PhysicsType::pSAND, sandColors, false, {0.0f, 3.0f}, { 0.0f,0.25f }, false, 0);

	std::array<RGB, 5> waterColors = { RGB{ 15,94,156,1}, RGB{20,85,156,1}, RGB{14,95,162,1}, RGB{28,100,152,1}, RGB{12,88,162,1} };
	water = ParticleContext(PhysicsType::pLIQUID, waterColors,true,{4.0f, 2.0f}, {1.0f, 0.2f}, false, 0);

	std::array<RGB, 5> woodColors = { RGB{ 85,51,17,1 }, RGB{102,68,51,1}, RGB{51,34,17,1}, RGB{153,102,51,1}, RGB{204,170,102,1} };
	wood = ParticleContext(PhysicsType::pSOLID, woodColors, false, {0.0f, 0.0f}, { 0.0f,0.0f }, false, 0);

	std::array<RGB, 5> smokeColors = { RGB{ 50,50,50,1 }, RGB{45,45,45,1}, RGB{55,55,55,1}, RGB{60,60,60,1}, RGB{48,48,48,1} };
	smoke = ParticleContext(PhysicsType::pGAS, smokeColors, true, {0.0f,0.0f}, {0.0f,0.0f}, true, 15);
}