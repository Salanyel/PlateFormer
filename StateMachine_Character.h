#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "State_Character_Base.h"
#include "Character.h"

using namespace sf;
using namespace std;

class StateMachine_Character
{
public:
	StateMachine_Character(Character * character);
	~StateMachine_Character();

	bool changeState(CHARACTER_STATES newState);
	Character * getCharacter();
	State_Character_Base * getCurrentState();

protected :
	Character * m_character;
	State_Character_Base * m_currentState;
};
