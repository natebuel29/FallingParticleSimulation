#include "ParticleContextManager.h"

ParticleContextManager::ParticleContextManager(){
	sand = ParticleContext(PhysicsType::SAND_, RGB{ 194,178,178,1 });
}

ParticleContext* ParticleContextManager::getParticleContext(ParticleType particle) {
	ParticleContext* particleContext = nullptr;

	switch (particle) {
		case ParticleType::SAND:
			particleContext = &sand;
	}
	
	return &sand;
}