#pragma once
#include "State_Character_Base.h"

class State_Character_Fly :
	public State_Character_Base
{
public:
	State_Character_Fly();
	~State_Character_Fly();

	bool changeStateAvailable(CHARACTER_STATES newState);
	bool initState();
	bool clearState();
	void operate();
};

