#include "Particles.h"

Particle createEmptyParticle() {
	Particle empty = Particle();
	empty.type = ParticleType::EMPTY;
	return empty;
}

Particle createSandParticle() {
	Particle sand = Particle();
	sand.type = ParticleType::SAND;
	return sand;
}

Particle createOutOfBoundsParticle() {
	Particle oob = Particle();
	oob.type = ParticleType::OUTOFBOUNDS;
	return oob;
}