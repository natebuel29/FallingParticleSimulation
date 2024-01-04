#include "ParticleContext.h"

PhysicsType ParticleContext::getPhysics() {
	return physics;
}

RGB* ParticleContext::getRGBFromArray(int index) {
	if (index > colors.size() - 1) {
		return &colors[0];
	}
	else {
		return &colors[index];
	}
}

bool ParticleContext::shouldUpdateColor() {
	return updateColor;
}

Vec2 ParticleContext::getMaxVel() {
	return maxVel;
}

Vec2 ParticleContext::getDVelocity() {
	return dVelocity;
}

uint8_t ParticleContext::getDecayRate() {
	return decayRate;
}

bool ParticleContext::shouldParticleDecay() {
	return shouldDecay;
}
bool ParticleContext::shouldParticleDissolve() {
	return isDissolvable;
}

bool ParticleContext::isParticleSwappable(ParticleType particle) {
	auto it = swappableParticles.find(particle);

	if (it == swappableParticles.end()) {
		return false;
	}
	else {
		return true;
	}
}
