#include "Tile.h"

Tile::Tile(TILE_TYPE type) : m_type(type)
{

}

Tile::~Tile()
{

}

TILE_TYPE Tile::getType()
{
	return m_type;
}

void Tile::setType(TILE_TYPE type)
{
	m_type = type;
}

bool Tile::isSolid()
{
	switch (m_type)
	{
	case T_BLOCK:
		return true;

	case T_MAPWALL:
		return true;

	default:
		return false;
	}
}

bool Tile::isNextLevel()
{
	if (m_type == T_NEXTLEVEL)
		return true;
	else
		return false;
}
