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
		case ParticleType::ACID:
			particleContext = &acid;
			break;
	}
	if (particleContext == nullptr) {
	//	Logger::getInstance()->error("AHHH NO PARTICLE CONTEXT SOMETHINGS GONE HORRIBLY WRONG");
	}
	return particleContext;
}

ParticleContextManager::ParticleContextManager() {
	std::array<RGB, 5> sandColors = { RGB{ 246,215,176}, RGB{242,210,169}, RGB{236,204,162}, RGB{231,196,150}, RGB{225,191,146} };
	sand = ParticleContext(PhysicsType::pSAND, sandColors, false, {0.0f, 3.0f}, { 0.0f,0.25f }, false, 0, false);

	std::array<RGB, 5> waterColors = { RGB{ 15,94,156}, RGB{20,85,156}, RGB{14,95,162}, RGB{28,100,152}, RGB{12,88,162} };
	water = ParticleContext(PhysicsType::pLIQUID, waterColors,true,{4.0f, 2.0f}, {4.0f, 0.2f}, false, 0, false);

	std::array<RGB, 5> woodColors = { RGB{ 85,51,17 }, RGB{102,68,51}, RGB{51,34,17}, RGB{153,102,51}, RGB{204,170,102} };
	wood = ParticleContext(PhysicsType::pSOLID, woodColors, false, {0.0f, 0.0f}, { 0.0f,0.0f }, false, 0, true);

	std::array<RGB, 5> smokeColors = { RGB{ 50,50,50 }, RGB{45,45,45}, RGB{55,55,55}, RGB{60,60,60}, RGB{48,48,48} };
	smoke = ParticleContext(PhysicsType::pGAS, smokeColors, true, {0.0f,0.0f}, {0.0f,0.0f}, true, 15, false);

	std::array<RGB, 5> acidColors = { RGB{ 143,254,9}, RGB{156,254,39}, RGB{186,254,104}, RGB{115,211,0}, RGB{102,186,0} };
	acid = ParticleContext(PhysicsType::pLIQUID, acidColors, true, { 2.0f, 2.0f }, { 1.0f, 0.2f }, false, 0, false);
}