#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "State_Game_Base.h"
#include "State_Game_Menu.h"

using namespace sf;
using namespace std;

enum GAME_STATES
{
	MENU,
	GAME
};

class StateMachine_Game
{
public:
	StateMachine_Game(RenderWindow * window);
	~StateMachine_Game();

	bool changeState(GAME_STATES newState);
	void operate();

	void setWindow(RenderWindow * window);
	RenderWindow * getWindow();
	State_Game_Base * getCurrentState();

protected:
	RenderWindow * m_window;
	State_Game_Base * m_currentState;
};

