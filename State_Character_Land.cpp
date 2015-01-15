#include "State_Character_Land.h"


State_Character_Land::State_Character_Land()
{
}


State_Character_Land::~State_Character_Land()
{
}

bool State_Character_Land::changeStateAvailable(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case STAND:
		return true;

	default : 
		return false;
	}
}
bool State_Character_Land::initState()
{
	return true;
}
bool State_Character_Land::clearState()
{
	return true;
}
void State_Character_Land::operate()
{
	
}