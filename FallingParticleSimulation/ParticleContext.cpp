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

float ParticleContext::getDecayProb() {
	return decayProb;
}

float ParticleContext::getDecayRate() {
	return decayRate;
}

float ParticleContext::getBurnProb() {
	return burnProb;
}

bool ParticleContext::isParticleFlammable() {
	return isFlammable;
}

bool ParticleContext::shouldParticleDecay() {
	return shouldDecay;
}
bool ParticleContext::shouldParticleDissolve() {
	return isDissolvable;
}
