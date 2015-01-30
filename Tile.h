#pragma once

#define TILE_SIZE 32

using namespace std;

enum TILE_TYPE{
	T_EMPTY=0,
	T_BLOCK,
	T_MAPWALL,
	T_SPAWN,
	T_NEXTLEVEL
};

class Tile
{
public:
	Tile(TILE_TYPE = T_EMPTY);
	~Tile();

	TILE_TYPE getType();
	void setType(TILE_TYPE type);

	bool isSolid();
	bool isNextLevel();

protected :
	TILE_TYPE m_type;


};

