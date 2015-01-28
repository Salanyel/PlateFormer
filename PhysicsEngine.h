#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Map.h"
#include "character.h"
#include "GraphicsEngine.h"
#include "CharacterImage.h"
#include "Momentum.h"

using namespace std;
using namespace sf;

enum PHYSIC_STATES
{
	MENU_PHYSICS,
	GAME_PHYSICS
};

class PhysicsEngine
{
public:
	PhysicsEngine(RenderWindow * window, GraphicsEngine * graphics);
	~PhysicsEngine();

	void setCurrentState(PHYSIC_STATES newState);
	void setWindow(RenderWindow * window);
	void setCharacter();
	bool initEngine();
	void collide();
	int collideY();
	int collideX();
	void fallingTest();
	void simulate();
	void saveMomentum();

	Character * getCharacter();
	Map * getMap();

protected:
	RenderWindow * m_window;
	GraphicsEngine * m_graphics;
	Map * m_map;
	PHYSIC_STATES m_currentState;

	Character * m_character;
	vector<Momentum *> * m_momentums;
};

