#pragma once
#include "ParticleContextManager.h"
#include "GameTiles.h"
#include <cstdlib> 

class ParticleHandler
{
	public:
		ParticleHandler();
		void handleParticle(GameTiles* gameTiles, int x, int y);
	private:
		void handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y);
};