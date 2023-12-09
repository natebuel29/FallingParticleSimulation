#pragma once
#include <vector>
#include <iostream>

class GameTiles
{
	public:
		GameTiles();
		GameTiles(int rows, int columns);

		int getTile(int x, int y, int xOffset, int yOffset);
		int getRowCount();
		int getColumnCount();
		bool setTile(int x, int y, int xOffset, int yOffset, int value);
		// swap tiles
		bool isInBounds(int x, int y, int xOffset, int yOffset);

	private:
		int rows;
		int columns;
		std::vector<std::vector<int>> gameTiles;
};

