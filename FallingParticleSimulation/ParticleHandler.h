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
		ParticleContextManager contextManager;
		void handleSand(GameTiles* gameTiles, int x, int y);
};

