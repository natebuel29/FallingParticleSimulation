#pragma once
#include "ParticleContextManager.h"
#include "GameTiles.h"
#include "Math.h"
#include <cstdlib> 

class ParticleHandler
{
	public:
		ParticleHandler();
		void handleParticle(GameTiles* gameTiles, int x, int y, int fpsCount);
	private:
		void handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleWater(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleAcid(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleLiquid(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleSolid(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleSmoke(GameTiles* gameTiles, ParticleContext* context, int x, int y);
		void handleDecay(GameTiles* gameTiles, Particle* particle, ParticleContext* context, int x, int y);
		void updateColor(Particle* particle);
		void handleAcidDissolve(GameTiles* gameTiles, Particle* particle, ParticleContext* context, int x, int y);
		void accelerateX(GameTiles* gameTiles, ParticleContext* context, int x,int y, int direction);
		void accelerateY(GameTiles* gameTiles, ParticleContext* context, int x, int y, int direction);
};