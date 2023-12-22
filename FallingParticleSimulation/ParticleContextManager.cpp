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
	}
	if (particleContext == nullptr) {
		Logger::getInstance()->error("AHHH NO PARTICLE CONTEXT SOMETHINGS GONE HORRIBLY WRONG");
	}
	return particleContext;
}

ParticleContextManager::ParticleContextManager() {
	sand = ParticleContext(PhysicsType::pSAND, RGB{ 194,178,128,1 });
	water = ParticleContext(PhysicsType::pLIQUID, RGB{ 15,94,156,1 });
	wood = ParticleContext(PhysicsType::pSOLID, RGB{ 86,61, 45, 1 });
}