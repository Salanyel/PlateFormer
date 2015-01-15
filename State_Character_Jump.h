#pragma once
#include "State_Character_Base.h"

class State_Character_Jump :
	public State_Character_Base
{
public:
	State_Character_Jump();
	~State_Character_Jump();

	bool changeStateAvailable(CHARACTER_STATES newState);
	bool initState();
	bool clearState();
	void operate();
};

