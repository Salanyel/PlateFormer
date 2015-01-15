#include "State_Character_Jump.h"


State_Character_Jump::State_Character_Jump()
{
}


State_Character_Jump::~State_Character_Jump()
{
}

bool State_Character_Jump::changeStateAvailable(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case CHARACTER_STATES::STAND:
		return true;

	default: 
		return false;
	}
}

bool State_Character_Jump::initState()
{
	return true;
}

bool State_Character_Jump::clearState()
{
	return true;
}

void State_Character_Jump::operate()
{

}