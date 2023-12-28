#pragma once
#include "PhysicsType.h"
#include "Particles.h"
#include "Colors.h"
#include "Math.h"
#include <array>

//Think of this as scriptable objects
class ParticleContext
{
	public:
		//this shouldn't be used but idk how to make it so we don't need
		ParticleContext() {}
		ParticleContext(PhysicsType phy, std::array<RGB, 5> colorArray, bool updateColor) : physics(phy), colors(colorArray), updateColor(updateColor) {}
		PhysicsType getPhysics();
		RGB* getRGBFromArray(int index);
		int getMaxVel();
		Vec2 getDVelocity();

		bool shouldUpdateColor();
	private:
		PhysicsType physics;
		std::array<RGB, 5> colors;
		bool updateColor;
		int maxVel = 3;
		Vec2 dVelocity = { 0.25f, 0.25f };
		//Passable materials will go here i.e. water goes to top of acid
		//bool isFlammable;
		//bool isCorrodible;
};

