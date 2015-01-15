#include "State_Character_Run.h"


State_Character_Run::State_Character_Run()
{
}


State_Character_Run::~State_Character_Run()
{
}

bool State_Character_Run::changeStateAvailable(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case STAND :
		return true;

	case JUMP :
		return true;

	default :
		return false;
	}
}

bool State_Character_Run::initState()
{
	return true;
}

bool State_Character_Run::clearState()
{
	return true;
}

void State_Character_Run::operate()
{

}