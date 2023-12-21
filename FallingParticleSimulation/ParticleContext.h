#pragma once
#include "PhysicsType.h"
#include "Colors.h"

//Think of this as scriptable objects
class ParticleContext
{
	public:
		//this shouldn't be used but idk how to make it so we don't need
		ParticleContext() {}
		ParticleContext(PhysicsType phy, RGB color) : physics(phy), rgb(color) {}
		PhysicsType getPhysics();
		RGB getRGB();
	private:
		PhysicsType physics;
		RGB rgb;
		//Passable materials will go here i.e. water goes to top of acid
		//bool isFlammable;
		//bool isCorrodible;
};

