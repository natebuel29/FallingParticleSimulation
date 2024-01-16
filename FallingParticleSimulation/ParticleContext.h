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
		ParticleContext(PhysicsType phy, std::array<RGB, 5> colorArray, bool updateColor, Vec2 maxVelocity, Vec2 velocity, bool shoDecay, float parDecayRate, float parDecayProb, bool dissolvable, bool flammable, float flammableProb) : physics(phy), colors(colorArray), updateColor(updateColor), dVelocity(velocity), maxVel(maxVelocity),shouldDecay(shoDecay), decayRate(parDecayRate),decayProb(parDecayProb), isDissolvable(dissolvable), isFlammable(flammable), burnProb(flammableProb) {}
		PhysicsType getPhysics();
		RGB* getRGBFromArray(int index);
		Vec2 getMaxVel();
		Vec2 getDVelocity();
		float getDecayRate();
		float getDecayProb();
		float getBurnProb();
		bool shouldUpdateColor();
		bool isParticleFlammable();
		bool shouldParticleDecay();
		bool shouldParticleDissolve();

	private:
		PhysicsType physics;
		std::array<RGB, 5> colors;
		Vec2 maxVel;
		Vec2 dVelocity;
		float decayRate;
		float decayProb;
		float burnProb;
		bool updateColor;
		bool shouldDecay;
		bool isDissolvable;
		bool isFlammable;
		//Passable materials will go here i.e. water goes to top of acid
		//bool isFlammable;
		//bool isCorrodible;
};

