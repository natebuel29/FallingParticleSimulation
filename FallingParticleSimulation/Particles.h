#pragma once
#include "Colors.h"
#include <stdint.h>
#include "Math.h"

enum ParticleType : uint8_t {
	EMPTY,
	OUTOFBOUNDS,
	SAND,
	WATER,
	WOOD
};

struct Particle {
	ParticleType type;
	uint8_t colorIndex;
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

static int PARTICLE_COLOR_COUNT = 5;

void updateCurrentParticle(ParticleCreationFunction& func, ParticleType particle);
