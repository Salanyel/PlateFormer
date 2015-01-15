#include "State_Character_Stand.h"


State_Character_Stand::State_Character_Stand()
{
}


State_Character_Stand::~State_Character_Stand()
{
}

bool State_Character_Stand::changeStateAvailable(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case CHARACTER_STATES::RUN :
		return true;

	case CHARACTER_STATES::JUMP:
		return true;

	default :
		return false;
	}
}

bool State_Character_Stand::initState()
{
	return true;
}

bool State_Character_Stand::clearState()
{
	return true;
}

void State_Character_Stand::operate()
{

}