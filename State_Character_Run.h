#pragma once
#include "State_Character_Base.h"

class State_Character_Run :
	public State_Character_Base
{
public:
	State_Character_Run();
	~State_Character_Run();

	bool changeStateAvailable(CHARACTER_STATES newState);
	bool initState();
	bool clearState();
	void operate();
};

