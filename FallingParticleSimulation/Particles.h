#pragma once
#include "Colors.h"
#include <stdint.h>

enum ParticleType : uint8_t {
	EMPTY,
	OUTOFBOUNDS,
	SAND,
	WATER,
	WOOD
};

struct Particle {
	ParticleType type;
	Color color;
	bool processed;
	//turn these on eventually
	//uint8_t life,
	//uint8_t decayRate
};

Particle createEmptyParticle();
Particle createSandParticle();
Particle createWaterParticle();
Particle createWoodParticle();

//Not a big fan of this but something needs to be returned when we out of bounds
Particle createOutOfBoundsParticle();

typedef Particle(*ParticleCreationFunction)();

void updateCurrentParticle(ParticleCreationFunction& func, ParticleType particle);
