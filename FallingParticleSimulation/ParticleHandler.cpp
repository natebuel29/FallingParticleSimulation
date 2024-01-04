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
		case PhysicsType::pGAS:
			if(((float)rand() / RAND_MAX) < 0.25f){
				handleGas(gameTiles, context, x, y);
			}
			break;
	}

	if (context->shouldParticleDecay()) {
		handleDecay(gameTiles, particle, context,x ,y);
	}

	if (particle->type == ACID) {
		handleAcidDissolve(gameTiles, particle, context, x, y);
	}


	// Handle corrosive
	// Handle flame
	// handle combining with neighbors
}

void ParticleHandler::handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	Particle current = gameTiles->getTile(x, y, 0, 0);
	Particle below = gameTiles->getTile(x, y, 0, 1);
	Particle lowRight = gameTiles->getTile(x, y, 1, 1);
	Particle lowLeft = gameTiles->getTile(x, y, -1, 1);

	ParticleContext* currentContext = ParticleContextManager::getInstance()->getParticleContext(current.type);
	ParticleContext* belowContext = ParticleContextManager::getInstance()->getParticleContext(below.type);
	ParticleContext* lowRightContext = ParticleContextManager::getInstance()->getParticleContext(lowRight.type);
	ParticleContext* lowLeftContext = ParticleContextManager::getInstance()->getParticleContext(lowLeft.type);


	if (currentContext->isParticleSwappable(below.type)) {
		accelerateY(gameTiles, context, x, y, 1);
	}
	else if (lowLeft.type == EMPTY || lowRight.type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (gameTiles->getTile(x, y, direction, 1).type == EMPTY) {
			Particle current = gameTiles->getTile(x, y, 0, 0);
			Particle target = gameTiles->getTile(x, y, direction, 1);
			current.processed = true;
			target.processed = true;
			gameTiles->setTile(x, y, direction, 1, current);
			gameTiles->setTile(x, y, 0, 0, target);
		}
	}
	//// TODO: THIS ISNT THE BEST WAY TO DO THIS. THIS MIGHT BREAK STUFF IN THE FUTURE!
	//// THE SWAPPABLE PARTICLE STUFF MIGHT WORK BETTER 
	// SEE COMMENTS ABOVE
	else if ((lowLeftContext != nullptr && lowLeftContext->getPhysics() == pLIQUID) ||
		(lowRightContext != nullptr && lowRightContext->getPhysics() == pLIQUID)) {
		if (((float)rand() / RAND_MAX) > 0.5f && lowRightContext != nullptr && lowRightContext->getPhysics() == pLIQUID) {
			int direction = 1;
			Particle current = gameTiles->getTile(x, y, 0, 0);
			current.processed = true;
			lowRight.processed = true;
			gameTiles->setTile(x, y, direction, 1, current);
			gameTiles->setTile(x, y, 0, 0, lowRight);
		}
		else if (lowLeftContext != nullptr && lowLeftContext->getPhysics() == pLIQUID) {
			int direction = -1;
			Particle current = gameTiles->getTile(x, y, 0, 0);
			current.processed = true;
			lowLeft.processed = true;
			gameTiles->setTile(x, y, direction, 1, current);
			gameTiles->setTile(x, y, 0, 0, lowLeft);
		}
	}
	else {
		gameTiles->getTileAddress(x, y, 0, 0)->vel = { 0.0f, 0.0f };

	}
}

void ParticleHandler::updateColor(Particle* particle) {
	particle->colorIndex = Math::getRandomInt(0, PARTICLE_COLOR_COUNT-1);
}

void ParticleHandler::handleSolid(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	//DO NOTHING BUT MAYBE THIS WILL DO SOMETHING IN FUTURE?!
}

void ParticleHandler::handleLiquid(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	Particle current = gameTiles->getTile(x, y, 0, 0);
	Particle below = gameTiles->getTile(x, y, 0, 1);
	Particle lowRight = gameTiles->getTile(x, y, 1, 1);
	Particle lowLeft = gameTiles->getTile(x, y, -1, 1);
	Particle right = gameTiles->getTile(x, y, 1, 0);
	Particle left = gameTiles->getTile(x, y, -1, 0);

	ParticleContext* belowContext = ParticleContextManager::getInstance()->getParticleContext(below.type);
	ParticleContext* lowRightContext = ParticleContextManager::getInstance()->getParticleContext(lowRight.type);
	ParticleContext* lowLeftContext = ParticleContextManager::getInstance()->getParticleContext(lowLeft.type);
	ParticleContext* rightContext = ParticleContextManager::getInstance()->getParticleContext(right.type);
	ParticleContext* leftContext = ParticleContextManager::getInstance()->getParticleContext(left.type);
	
	if (below.type == EMPTY) {
		accelerateY(gameTiles, context, x, y, 1);
	}
	else if (lowLeft.type == EMPTY) {
		current.processed = true;
		lowLeft.processed = true;
		gameTiles->setTile(x, y, -1, 1, current);
		gameTiles->setTile(x, y, 0, 0, lowLeft);
	}
	else if (lowRight.type == EMPTY) {
		current.processed = true;
		lowRight.processed = true;
		gameTiles->setTile(x, y, 1, 1, current);
		gameTiles->setTile(x, y, 0, 0, lowRight);
	}
	else if (current.vel.x > 0.0f && (right.type == EMPTY || right.type == WATER || right.type == ACID)) {
		accelerateX(gameTiles, context, x, y, 1);
	}
	else if (current.vel.x < 0.0f && (left.type == EMPTY || left.type == WATER || left.type == ACID)) {
		accelerateX(gameTiles, context, x, y, -1);
	}
	else if (left.type == EMPTY && right.type == EMPTY) {
		if (((float)rand() / RAND_MAX) > 0.5f && gameTiles->getTile(x, y, 1, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, 1);
		}
		else if (gameTiles->getTile(x, y, -1, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, -1);
		}
	}
	else if (left.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);

	}
	else if (right.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, 1);
	}
	else {
		gameTiles->getTileAddress(x, y, 0, 0)->vel = { 0.0f,0.0f };
	}
}

void ParticleHandler::handleGas(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	Particle current = gameTiles->getTile(x, y, 0, 0);
	Particle up = gameTiles->getTile(x, y, 0, -1);
	Particle upRight = gameTiles->getTile(x, y, 1, -1);
	Particle upLeft = gameTiles->getTile(x, y, -1, -1);
	Particle right = gameTiles->getTile(x, y, 1, 0);
	Particle left = gameTiles->getTile(x, y, -1, 0);

	ParticleContext* belowContext = ParticleContextManager::getInstance()->getParticleContext(up.type);
	ParticleContext* lowRightContext = ParticleContextManager::getInstance()->getParticleContext(upRight.type);
	ParticleContext* lowLeftContext = ParticleContextManager::getInstance()->getParticleContext(upLeft.type);
	ParticleContext* rightContext = ParticleContextManager::getInstance()->getParticleContext(right.type);
	ParticleContext* leftContext = ParticleContextManager::getInstance()->getParticleContext(left.type);

	if (up.type == EMPTY ) {
		accelerateY(gameTiles, context, x, y, -1);
	}
	else if (upLeft.type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		current.processed = true;
		upLeft.processed = true;
		gameTiles->setTile(x, y, -1, -1, current);
		gameTiles->setTile(x, y, 0, 0, upLeft);
	}
	else if (upRight.type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		current.processed = true;
		upRight.processed = true;
		gameTiles->setTile(x, y, 1, -1, current);
		gameTiles->setTile(x, y, 0, 0, upRight);
	}
	else if (current.vel.x > 0.0f && right.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, 1);
	}

	else if( current.vel.x < 0.0f && left.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);
	}
	else if (left.type == EMPTY &&right.type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (((float)rand() / RAND_MAX) > 0.5f && gameTiles->getTile(x, y, 1, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, 1);
		}
		else if (gameTiles->getTile(x, y, -1, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, -1);
		}
	}
	else if (left.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);

	}
	else if (right.type == EMPTY) {
		accelerateX(gameTiles, context, x, y, 1);
	}
}


void ParticleHandler::accelerateX(GameTiles* gameTiles, ParticleContext* context, int x, int y, int direction){
	int openTile = direction;

	Particle current = gameTiles->getTile(x, y, 0, 0);
	current.vel.x += (context->getDVelocity().x) * direction;
	if (std::abs(current.vel.x) > context->getMaxVel().x) {
		current.vel.x = context->getMaxVel().x * direction;
	}

	for (int i = std::abs(direction); i <= std::abs(direction * current.vel.x); i++) {
		int target = i * direction;
		if (!gameTiles->getTileAddress(x, y, target, 0)->type == EMPTY) {
			if (gameTiles->getTileAddress(x, y, target, 0)->type == OUTOFBOUNDS) {
				current.vel.x = 0.0f;
			}
			break;

		}
		else {
			openTile = target;
		}
	}

	Particle target = gameTiles->getTile(x, y, openTile, 0);
	current.processed = true;
	target.processed = true;
	gameTiles->setTile(x, y, openTile, 0, current);
	gameTiles->setTile(x, y, 0, 0, target);
}

void ParticleHandler::handleAcidDissolve(GameTiles* gameTiles, Particle* particle, ParticleContext* context, int x, int y) {
	Particle below = gameTiles->getTile(x, y, 0, 1);
	Particle right = gameTiles->getTile(x, y, 1, 0);
	Particle left = gameTiles->getTile(x, y, -1, 0);
	ParticleContext* belowContext = ParticleContextManager::getInstance()->getParticleContext(below.type);
	ParticleContext* rightContext = ParticleContextManager::getInstance()->getParticleContext(right.type);
	ParticleContext* leftContext = ParticleContextManager::getInstance()->getParticleContext(left.type);



	if (belowContext != nullptr && belowContext->shouldParticleDissolve() && ((float)rand() / RAND_MAX) < 0.65f) {
		gameTiles->setTile(x, y, 0, 1, createEmptyParticle());
	}
	else if (rightContext != nullptr && rightContext->shouldParticleDissolve() && ((float)rand() / RAND_MAX) < 0.65f) {
		gameTiles->setTile(x, y, 1, 0, createEmptyParticle());
	}
	else if (leftContext != nullptr && leftContext->shouldParticleDissolve() && ((float)rand() / RAND_MAX) < 0.65f) {
		gameTiles->setTile(x, y, -1, 0, createEmptyParticle());
	}

}

void ParticleHandler::accelerateY(GameTiles* gameTiles, ParticleContext* context, int x, int y, int direction) {
	int openTile = direction;

	Particle current = gameTiles->getTile(x, y, 0, 0);
	current.vel.y += (context->getDVelocity().y) * direction;
	if (std::abs(current.vel.y) > context->getMaxVel().y) {
		current.vel.y = context->getMaxVel().y * direction;
	}

	for (int i = std::abs(direction); i <= std::abs(direction *((int) current.vel.y)); i++) {
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

void ParticleHandler::handleDecay(GameTiles* gameTiles, Particle* particle, ParticleContext* context, int x, int y) {
	if (((float)rand() / RAND_MAX) < 0.03f) {
		particle->alpha = particle->alpha - context->getDecayRate();
		if (particle->alpha <= 0) {
			gameTiles->setTile(x, y, 0, 0, createEmptyParticle());
		}
	}
}