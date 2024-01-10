#pragma once
#include <array>
#include <iostream>
#include "Logger.h"
#include "Particles.h"


//TODO: modify this so we can use templates so the tiles can be used for any type
// For example GameTiles intTile = new GameTiles<int>();
class GameTiles
{
	public:
		GameTiles();
		GameTiles(int rows, int columns);

		Particle getTile(int x, int y, int xOffset, int yOffset);
		Particle* getTileAddress(int x, int y, int xOffset, int yOffset);
		int getRowCount();
		int getColumnCount();
		bool setTile(int x, int y, int xOffset, int yOffset, Particle value);
		// swap tiles
		bool isInBounds(int x, int y, int xOffset, int yOffset);

	private:
		int rows;
		int columns;
		std::vector<std::vector<Particle>> gameTiles;
};

