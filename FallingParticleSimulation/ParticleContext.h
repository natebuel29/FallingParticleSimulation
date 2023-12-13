#pragma once
#include "PhysicsType.h"
#include "Colors.h"

class ParticleContext
{
	public:
	private:
		PhysicsType physics;
		RGB rgb;
		//Passable materials will go here i.e. water goes to top of acid
		bool isFlammable;
		bool isCorrodible;
};

