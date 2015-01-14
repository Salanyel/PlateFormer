#include "StateMachine_Character.h"


StateMachine_Character::StateMachine_Character(Character * character) : m_character(character)
{
}


StateMachine_Character::~StateMachine_Character()
{
}

bool StateMachine_Character::changeState(CHARACTER_STATES newState)
{
	return true;
}

Character * StateMachine_Character::getCharacter()
{
	return m_character;
}

/*State_Character_Base * StateMachine_Character::getCurrentState()
{
	return m_currentState;
}*/