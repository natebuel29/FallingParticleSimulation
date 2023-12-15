#include "ParticleHandler.h"

ParticleHandler::ParticleHandler() {
}

void ParticleHandler::handleParticle(GameTiles* gameTiles, int x, int y) {
	Particle particle = gameTiles->getTile(x, y, 0, 0);
	ParticleContext* context = ParticleContextManager::getInstance()->getParticleContext(particle.type);

	// Handle Physic
	switch (context->getPhysics()) {
		case PhysicsType::pSAND:
			handleSand(gameTiles, context, x, y);
	}


	// Handle corrosive
	// Handle flame
	// handle combining with neighbors
}

void ParticleHandler::handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y){
	Particle sand = gameTiles->getTile(x, y, 0, 0);
	if (gameTiles->getTile(x, y, 0, 1).type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		Particle target = gameTiles->getTile(x, y, 0, 1);
		gameTiles->setTile(x, y, 0, 1, current);
		gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTile(x, y, -1, 1).type == EMPTY || gameTiles->getTile(x, y, 1, 1).type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;

		if (gameTiles->getTile(x, y, direction, 1).type == EMPTY) {
			Particle current = gameTiles->getTile(x, y, 0, 0);
			Particle target = gameTiles->getTile(x, y, direction, 1);
			gameTiles->setTile(x, y, direction, 1, current);
			gameTiles->setTile(x, y, 0, 0, target);
		}
	}
}