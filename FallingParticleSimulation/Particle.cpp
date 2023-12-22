#include "Particles.h"

Particle createEmptyParticle() {
	Particle empty = Particle();
	empty.type = ParticleType::EMPTY;
	return empty;
}

Particle createSandParticle() {
	Particle sand = Particle();
	sand.type = ParticleType::SAND;
	sand.color = Color::LIGHT_BROWN;
	return sand;
}

Particle createWaterParticle() {
	Particle water = Particle();
	water.type = ParticleType::WATER;
	water.color = Color::LIGHT_BROWN;
	return water;
}

Particle createWoodParticle() {
	Particle wood = Particle();
	wood.type = ParticleType::WOOD;
	wood.color = Color::LIGHT_BROWN;
	return wood;
}

Particle createOutOfBoundsParticle() {
	Particle oob = Particle();
	oob.type = ParticleType::OUTOFBOUNDS;
	return oob;
}

void updateCurrentParticle(ParticleCreationFunction& func, ParticleType particle) {
	switch (particle) {
		case SAND:
			func = createSandParticle;
			break;
		case WATER:
			func = createWaterParticle;
			break;
		case WOOD:
			func = createWoodParticle;
			break;
		default:
			func = createSandParticle;
			break;
	}
}