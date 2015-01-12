#pragma once
#include <SFML/Graphics.hpp>

class CharacterImage
{
public:
	CharacterImage();
	~CharacterImage();

	int getX();
	int getY();

	void setX(int x);
	void setY(int Y);
	void move(int x, int y);

protected :
	int m_x;
	int m_y;
};