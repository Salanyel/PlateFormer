#pragma once
#include "CharacterImage.h"
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

#define MOVE_VELOCITY 4;
#define JUMP_VELOCITY 10;

class Character
{
public:
	Character();
	~Character();
	
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	CharacterImage * getCharacterImage();
	void move(int x, int y);
	void processEvents(Event event);
	void processEvents();
	
protected :
	int m_x;
	int m_y;
	int m_orientation;
	CharacterImage * m_image;
};