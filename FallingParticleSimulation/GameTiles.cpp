#include "GameTiles.h"

//public
// Default constructor providing a default state
GameTiles::GameTiles() : rows(0), columns(0) {
}

GameTiles::GameTiles(int r, int c) : rows(r), columns(c) {
	gameTiles = std::vector<std::vector<Particle>>(rows, std::vector<Particle>(columns, createEmptyParticle()));

}

//Should this return a pointer?
//Should there be another function that 
Particle GameTiles::getTile(int x, int y, int xOffset, int yOffset) {
	if (isInBounds( x,  y,  xOffset,  yOffset)) {
		return gameTiles[x + xOffset][y + yOffset];
	}
	else {
	//	Logger::getInstance()->warn("ERROR WE ARE OUT OF BOUNDS");
		return createOutOfBoundsParticle();
	}
}

Particle* GameTiles::getTileAddress(int x, int y, int xOffset, int yOffset) {
	if (isInBounds(x, y, xOffset, yOffset)) {
		return &gameTiles[x + xOffset][y + yOffset];
	}
	else {
		//	Logger::getInstance()->warn("ERROR WE ARE OUT OF BOUNDS");
		Particle oob = createOutOfBoundsParticle();
		return &oob;
	}
}

int GameTiles::getRowCount() {
	return rows;
}

int GameTiles::getColumnCount() {
	return columns;
}

bool GameTiles::setTile(int x, int y, int xOffset, int yOffset, Particle value) {
	if (isInBounds( x,  y,  xOffset,  yOffset)) {
		gameTiles[x + xOffset][y + yOffset] = value;
		return true;
	}
	else {
	// commenting this out because of performance
	//	Logger::getInstance()->warn("ERROR WE ARE OUT OF BOUNDS");
		return false;
	}
}

bool GameTiles::isInBounds(int x, int y, int xOffset, int yOffset) {
	return (x + xOffset < rows && x + xOffset >= 0 && y + yOffset >= 0 && y + yOffset < columns);
}