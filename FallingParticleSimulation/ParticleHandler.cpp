#include "ParticleHandler.h"

ParticleHandler::ParticleHandler() {
}

void ParticleHandler::handleParticle(GameTiles* gameTiles, int x, int y, int fpsCount) {
	Particle* particle = gameTiles->getTileAddress(x, y, 0, 0);
	ParticleContext* context = ParticleContextManager::getInstance()->getParticleContext(particle->type);

	////Handle color update
	if ( context->shouldUpdateColor()) {
		updateColor(particle);
	}

	// Handle Physic
	switch (context->getPhysics()) {
		case PhysicsType::pSAND:
			handleSand(gameTiles, context, x, y);
			break;
		case PhysicsType::pLIQUID:
			handleLiquid(gameTiles, context, x, y);
			break;
	}


	// Handle corrosive
	// Handle flame
	// handle combining with neighbors
}

void ParticleHandler::handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y){
	if (gameTiles->getTile(x, y, 0, 1).type == EMPTY || gameTiles->getTile(x, y, 0, 1).type == WATER) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		current.vel += 1;
		if (current.vel > 3) {
			current.vel = 3;
		}
		accelerateDown(gameTiles, x, y, 1, current.vel);
	}
	else if (gameTiles->getTile(x, y, -1, 1).type == EMPTY || gameTiles->getTile(x, y, 1, 1).type == EMPTY || gameTiles->getTile(x, y, -1, 1).type == WATER || gameTiles->getTile(x, y, 1, 1).type == WATER) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (gameTiles->getTile(x, y, direction, 1).type == EMPTY || gameTiles->getTile(x, y, direction, 1).type == WATER) {
			Particle current = gameTiles->getTile(x, y, 0, 0);
			Particle target = gameTiles->getTile(x, y, direction, 1);
			current.processed = true;
			target.processed = true;
			gameTiles->setTile(x, y, direction, 1, current);
			gameTiles->setTile(x, y, 0, 0, target);
		}
	}
	//// TODO: THIS ISNT THE BEST WAY TO DO THIS. THIS MIGHT BREAK STUFF IN THE FUTURE!
	//// THE SWAPPABLE PARTICLE STUFF MIGHT WORK BETTER FOR THIS
	//else if (gameTiles->getTile(x, y, 0, 1).type == WATER) {
	//	Particle target = gameTiles->getTile(x, y, 0, 1);
	//	Particle current = gameTiles->getTile(x, y, 0, 0);
	//	current.processed = true;
	//	target.processed = true;
	//	gameTiles->setTile(x, y, 0, 1, current);
	//	gameTiles->setTile(x, y, 0, 0, target);

	//}
	//// SEE COMMENTS ABOVE
	//else if (gameTiles->getTile(x, y, 1, 1).type == WATER ||
	//	gameTiles->getTile(x, y, -1, 1).type == WATER) {
	//	int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
	//	Particle target = gameTiles->getTile(x, y, direction, 1);
	//	ParticleContext* targetContext = ParticleContextManager::getInstance()->getParticleContext(target.type);

	//	if (targetContext != nullptr &&targetContext->getPhysics() == pLIQUID) {
	//		Particle current = gameTiles->getTile(x, y, 0, 0);
	//		current.processed = true;
	//		target.processed = true;
	//		gameTiles->setTile(x, y, direction, 1, current);
	//		gameTiles->setTile(x, y, 0, 0, target);
	//	}
	//}
}

void ParticleHandler::updateColor(Particle* particle) {
	particle->colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT-1);
}

void ParticleHandler::handleSolid(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	//DO NOTHING BUT MAYBE THIS WILL DO SOMETHING IN FUTURE?!
}

void ParticleHandler::handleLiquid(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	int disperseRate = 3;

	if (gameTiles->getTileAddress(x, y, 0, 1)->type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		Particle target = gameTiles->getTile(x, y, 0, 1);
		current.processed = true;
		target.processed = true;
		gameTiles->setTile(x, y, 0, 1, current);
		gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTileAddress(x, y, -1, 1)->type == EMPTY) {
			Particle current = gameTiles->getTile(x, y, 0, 0);
			Particle target = gameTiles->getTile(x, y, -1, 1);
			current.processed = true;
			target.processed = true;
			gameTiles->setTile(x, y, -1, 1, current);
			gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTileAddress(x, y, 1, 1)->type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		Particle target = gameTiles->getTile(x, y, 1, 1);
		current.processed = true;
		target.processed = true;
		gameTiles->setTile(x, y, 1, 1, current);
		gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY && gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (gameTiles->getTile(x, y, direction, 0).type == EMPTY) {
			disperse(gameTiles, x, y, direction, disperseRate);
		}
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY) {
		disperse(gameTiles, x, y, -1, disperseRate);

	}
	else if (gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		disperse(gameTiles, x, y, 1, disperseRate);
	}
}

void ParticleHandler::disperse(GameTiles* gameTiles, int x, int y, int direction, int disperseRate) {
	int openTile = direction;

	for (int i = std::abs(direction); i <= std::abs(direction * disperseRate); i++) {
		int target = i * direction;
		if (!gameTiles->getTile(x, y, target, 0).type == EMPTY) {
			break;
		}
		else {
			openTile = target;
		}
	}

	Particle current = gameTiles->getTile(x, y, 0, 0);
	Particle target = gameTiles->getTile(x, y, openTile, 0);
	current.processed = true;
	target.processed = true;
	gameTiles->setTile(x, y, openTile, 0, current);
	gameTiles->setTile(x, y, 0, 0, target);
}

void ParticleHandler::accelerateDown(GameTiles* gameTiles, int x, int y, int direction, int disperseRate) {
	int openTile = direction;

	Particle current = gameTiles->getTile(x, y, 0, 0);
	current.vel += 1;
	if (current.vel > 3) {
		current.vel = 3;
	}

	for (int i = std::abs(direction); i <= std::abs(direction * disperseRate); i++) {
		int target = i * direction;
		if (!gameTiles->getTile(x, y, 0, target).type == EMPTY) {
			break;
		}
		else {
			openTile = target;
		}
	}

	Particle target = gameTiles->getTile(x, y, 0, openTile);
	current.processed = true;
	target.processed = true;
	gameTiles->setTile(x, y, 0, openTile, current);
	gameTiles->setTile(x, y, 0, 0, target);
}