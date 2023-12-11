#pragma once

enum ParticleType {
	EMPTY,
	OUTOFBOUNDS,
	SAND
};

struct Particle {
	ParticleType type;
};

Particle createEmptyParticle();
Particle createSandParticle();
Particle createOutOfBoundsParticle();