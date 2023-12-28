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

int ParticleContext::getMaxVel() {
	return maxVel;
}

Vec2 ParticleContext::getDVelocity() {
	return dVelocity;
}