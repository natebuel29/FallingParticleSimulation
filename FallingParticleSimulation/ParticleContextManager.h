#pragma once
#include "ParticleContext.h"
#include "Particles.h"
#include "Logger.h"
#include <string>
#include <array>
#include "Math.h"


class ParticleContextManager
{
public:
	ParticleContext* getParticleContext(ParticleType particle);
	
	void operator=(const ParticleContextManager& other) = delete;
	
	ParticleContextManager(const ParticleContextManager& other) = delete;

	static ParticleContextManager* getInstance();

	static ParticleContextManager* instance;
private:
	ParticleContext sand;
	ParticleContext water;
	ParticleContext wood;
	ParticleContext smoke;
	ParticleContext acid;
	
	ParticleContextManager();
};


