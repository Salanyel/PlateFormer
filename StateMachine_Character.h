#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "State_Character_Base.h"
#include "State_Character_Stand.h"
#include "State_Character_Run.h"
#include "State_Character_Jump.h"
#include "State_Character_Fly.h"
#include "State_Character_Land.h"

using namespace sf;
using namespace std;

class StateMachine_Character
{
public:
	StateMachine_Character();
	~StateMachine_Character();

	bool changeState(CHARACTER_STATES newState);
	bool forceChangeState(CHARACTER_STATES newState);
	State_Character_Base * getCurrentState();
	CHARACTER_STATES getIdCurrentState();

protected :
	State_Character_Base * m_currentState;
	CHARACTER_STATES m_stateId;
};
