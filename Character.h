#pragma once
#include "CharacterImage.h"
#include <iostream>

using namespace std;

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
	
protected :
	int m_x;
	int m_y;
	CharacterImage * m_image;
};

