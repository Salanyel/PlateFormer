#include "State_Character_Fly.h"


State_Character_Fly::State_Character_Fly()
{
}


State_Character_Fly::~State_Character_Fly()
{
}

bool State_Character_Fly::changeStateAvailable(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case LAND :
		return true;

	default :
		return false;
	}
}
bool State_Character_Fly::initState()
{
	return true;
}

bool State_Character_Fly::clearState()
{
	return true;
}

void State_Character_Fly::operate()
{

}