#pragma once
#include "ParticleContext.h"
#include "Particles.h"
#include <string>

class ParticleContextManager
{
	public:
		ParticleContextManager();
		ParticleContext* getParticleContext(ParticleType particle);

	private:
		ParticleContext sand;
};

