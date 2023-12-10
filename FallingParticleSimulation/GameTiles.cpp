#include "GameTiles.h"

//public
// Default constructor providing a default state
GameTiles::GameTiles() : rows(0), columns(0.0) {
}

GameTiles::GameTiles(int r,int c) : gameTiles(rows, std::vector<int>(columns, 0)),rows(r),columns(c) {
}

int GameTiles::getTile(int x, int y, int xOffset, int yOffset) {
	if (isInBounds( x,  y,  xOffset,  yOffset)) {
		return gameTiles[x + xOffset][y + yOffset];
	}
	else {
		Logger::getInstance()->warn("ERROR WE ARE OUT OF BOUNDS");
		return -1;
	}
}

int GameTiles::getRowCount() {
	return rows;
}

int GameTiles::getColumnCount() {
	return columns;
}

bool GameTiles::setTile(int x, int y, int xOffset, int yOffset, int value) {
	if (isInBounds( x,  y,  xOffset,  yOffset)) {
		gameTiles[x + xOffset][y + yOffset] = value;
		return true;
	}
	else {
		Logger::getInstance()->warn("ERROR WE ARE OUT OF BOUNDS");
		return false;
	}
}

bool GameTiles::isInBounds(int x, int y, int xOffset, int yOffset) {
	return (x + xOffset < rows && x - xOffset >= 0 && y - yOffset < columns && y + yOffset >= 0);
}