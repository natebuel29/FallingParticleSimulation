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

void ParticleHandler::handleSand(GameTiles* gameTiles, ParticleContext* context, int x, int y){
	if (gameTiles->getTile(x, y, 0, 1).type == EMPTY || gameTiles->getTile(x, y, 0, 1).type == WATER) {
		accelerateY(gameTiles, context, x, y, 1);
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
	else {
		gameTiles->getTileAddress(x, y, 0, 0)->vel = {0.0f, 0.0f};
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
	if (gameTiles->getTileAddress(x, y, 0, 1)->type == EMPTY) {
		accelerateY(gameTiles, context, x, y, 1);
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
	else if (gameTiles->getTileAddress(x, y, 0, 0)->vel.x > 0.0f && (gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY || gameTiles->getTileAddress(x, y, 1, 0)->type == WATER)) {
		accelerateX(gameTiles, context, x, y, 1);
	}

	else if (gameTiles->getTileAddress(x, y, 0, 0)->vel.x < 0.0f && (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY || gameTiles->getTileAddress(x, y, -1, 0)->type == WATER)) {
		accelerateX(gameTiles, context, x, y, -1);
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY && gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (gameTiles->getTile(x, y, direction, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, direction);
		}
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);

	}
	else if (gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		accelerateX(gameTiles, context, x, y, 1);
	}
	else {
		gameTiles->getTileAddress(x, y, 0, 0)->vel = { 0.0f,0.0f };
	}
}

void ParticleHandler::handleGas(GameTiles* gameTiles, ParticleContext* context, int x, int y) {
	if (gameTiles->getTileAddress(x, y, 0, -1)->type == EMPTY ) {
		accelerateY(gameTiles, context, x, y, -1);
	}
	else if (gameTiles->getTileAddress(x, y, -1, -1)->type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		Particle target = gameTiles->getTile(x, y, -1, -1);
		current.processed = true;
		target.processed = true;
		gameTiles->setTile(x, y, -1, -1, current);
		gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTileAddress(x, y, 1, -1)->type == EMPTY) {
		Particle current = gameTiles->getTile(x, y, 0, 0);
		Particle target = gameTiles->getTile(x, y, 1, -1);
		current.processed = true;
		target.processed = true;
		gameTiles->setTile(x, y, 1, -1, current);
		gameTiles->setTile(x, y, 0, 0, target);
	}
	else if (gameTiles->getTileAddress(x, y, 0, 0)->vel.x > 0.0f && gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		accelerateX(gameTiles, context, x, y, 1);
	}

	else if (gameTiles->getTileAddress(x, y, 0, 0)->vel.x < 0.0f && gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY && gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
		int direction = ((float)rand() / RAND_MAX) > 0.5f ? 1 : -1;
		if (gameTiles->getTile(x, y, direction, 0).type == EMPTY) {
			accelerateX(gameTiles, context, x, y, direction);
		}
	}
	else if (gameTiles->getTileAddress(x, y, -1, 0)->type == EMPTY) {
		accelerateX(gameTiles, context, x, y, -1);

	}
	else if (gameTiles->getTileAddress(x, y, 1, 0)->type == EMPTY) {
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
	if (below.type == OUTOFBOUNDS) {
		return;
	}
	ParticleContext* belowContext = ParticleContextManager::getInstance()->getParticleContext(below.type);

	if (belowContext != nullptr && belowContext->shouldParticleDissolve() && ((float)rand() / RAND_MAX) < 0.1f) {
		gameTiles->setTile(x, y, 0, 1, createEmptyParticle());
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