#include "Particles.h"

Particle createEmptyParticle() {
	Particle empty = Particle();
	empty.type = ParticleType::EMPTY;
	empty.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT - 1);
	empty.vel = { 0.0f,0.0f };
	empty.processed = false;
	empty.alpha = 255;
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

Particle createAcidParticle() {
	Particle acid = Particle();
	acid.type = ParticleType::ACID;
	acid.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT - 1);
	acid.processed = false;
	acid.alpha = 255;
	return acid;
}

Particle createFireParticle() {
	Particle fire = Particle();
	fire.type = ParticleType::FIRE;
	fire.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT - 1);
	fire.processed = false;
	fire.alpha = 255;
	return fire;
}

Particle createIceParticle(){
	Particle ice = Particle();
	ice.type = ParticleType::ICE;
	ice.colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT - 1);
	ice.processed = false;
	ice.alpha = 255;
	return ice;
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
		case ACID:
			func = createAcidParticle;
			break;
		case FIRE:
			func = createFireParticle;
			break;
		case ICE:
			func = createIceParticle;
			break;
		case EMPTY:
			func = createEmptyParticle;
			break;
		default:
			func = createSandParticle;
			break;
	}
}