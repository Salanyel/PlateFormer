#pragma once
#include "State_Character_Base.h"

class State_Character_Land :
	public State_Character_Base
{
public:
	State_Character_Land();
	~State_Character_Land();

	bool changeStateAvailable(CHARACTER_STATES newState);
	bool initState();
	bool clearState();
	void operate();
};

