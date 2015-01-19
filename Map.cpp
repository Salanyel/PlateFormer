#include "Map.h"


Map::Map(char_t * path)
{
	m_path = path;
}

Map::~Map()
{
	delete(m_path);
}

Tile * Map::getTile(int x, int y)
{

	int yPlace = y * m_mapWidth;
	//cout << "X : " << x << " / Y : " << y << " // yPlace : " << y * m_mapHeight<< " // Place : " << yPlace + x << endl;

	return m_tiles.at(x + yPlace);
}

Tile * Map::getTile(int tileNumber)
{
	return m_tiles.at(tileNumber);
}

int Map::getMapHeight()
{
	return m_mapHeight;
}

int Map::getMapWidth()
{
	return m_mapWidth;
}

int Map::getTileNumber()
{
	return m_mapWidth * m_mapHeight;
}

bool Map::loadMap()
{
	xml_document doc;
	xml_parse_result resultDoc;
	xml_node map;
	xml_node tileXml;

	resultDoc = doc.load_file(m_path);

	if (!resultDoc)
	{
		cout << "Error during the loading of the maps.xml" << endl;
		return false;
	}

	cout << "Maps file loaded." << endl;

	map = doc.child("Maps");
	map = map.child("Map");

	for (xml_node tool = map.first_child(); tool; tool = tool.next_sibling())
	{	
		if (strcmp(tool.name(),"MapInfo") == 0)
		{
			m_mapWidth = atoi(tool.attribute("width").value());
			m_mapHeight = atoi(tool.attribute("height").value());
			cout << "Map size : " << m_mapWidth << " x " << m_mapHeight << endl;
		}

		if (strcmp(tool.name(), "Tiles") == 0)
		{
			Tile * tile;
			for (tileXml = tool.child("Tile"); tileXml; tileXml = tileXml.next_sibling("Tile"))
			{			
				tile = new Tile();
				switch (atoi(tileXml.attribute("value").value()))
				{
				case 0:
					tile->setType(T_EMPTY);
					m_tiles.push_back(tile);
					break;

				case 1:
					tile->setType(T_BLOCK);
					m_tiles.push_back(tile);
					break;

				case 2:
					tile->setType(T_MAPWALL);
					m_tiles.push_back(tile);
					break;

				case 3:
					tile->setType(T_SPAWN);
					m_tiles.push_back(tile);
					break;
				}		
			}
		}
	}
}

void Map::loadTestMap()
{

}

void Map::display()
{
	
	int it;
	int ctrl = 0;
	for (it = 0; it < m_tiles.size(); ++it)
	{
		cout << m_tiles.at(it)->getType() << " ";
		++ctrl;
		if (ctrl == m_mapWidth)
		{
			ctrl = 0;
			cout << endl;
		}
	}
}