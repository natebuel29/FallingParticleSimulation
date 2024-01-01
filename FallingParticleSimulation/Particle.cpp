#include "Particles.h"

Particle createEmptyParticle() {
	Particle empty = Particle();
	empty.type = ParticleType::EMPTY;
	return empty;
}

Particle createSandParticle() {
	Particle sand = Particle();
	sand.type = ParticleType::SAND;
	sand.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT-1);
	sand.vel = {0.0f,0.0f};
	sand.processed = false;
	sand.alpha = 255;
	return sand;
}

Particle createWaterParticle() {
	Particle water = Particle();
	water.type = ParticleType::WATER;
	water.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT-1);
	water.vel = { 0.0f,0.0f };
	water.processed = false;
	water.alpha = 255;
	return water;
}

Particle createWoodParticle() {
	Particle wood = Particle();
	wood.type = ParticleType::WOOD;
	wood.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT-1);
	wood.processed = false;
	wood.alpha = 255;
	return wood;
}

Particle createSmokeParticle() {
	Particle smoke = Particle();
	smoke.type = ParticleType::SMOKE;
	smoke.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT - 1);
	smoke.processed = false;
	smoke.alpha = 255;
	return smoke;
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
		case SMOKE:
			func = createSmokeParticle;
			break;
		case EMPTY:
			func = createEmptyParticle;
			break;
		default:
			func = createSandParticle;
			break;
	}
}