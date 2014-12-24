#pragma once

#include "Tile.h"
#include <vector>
#include <iostream>
#include <pugixml.hpp>

using namespace std;
using namespace pugi;

class Map
{
public:
	Map(char_t * path = "Assets/Maps/maps.xml");
	~Map();

	Tile * getTile(int x, int y);
	Tile * getTile(int tileNumber);

	int getMapHeight();
	int getMapWidth();
	int getTileNumber();

	bool loadMap();
	void loadTestMap();

	void display();

protected:
	std::vector<Tile *> m_tiles;
	int m_mapHeight;
	int m_mapWidth;
	char_t * m_path;
};

