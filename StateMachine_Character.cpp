#include "StateMachine_Character.h"


StateMachine_Character::StateMachine_Character()
{
	forceChangeState(CHARACTER_STATES::STAND);
}

StateMachine_Character::~StateMachine_Character()
{
}

bool StateMachine_Character::changeState(CHARACTER_STATES newState)
{
	if (!m_currentState->changeStateAvailable(newState))
		return false;

	switch (newState)
	{
	case CHARACTER_STATES::STAND:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : STAND" << endl;
		m_currentState = new State_Character_Stand();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;

	case CHARACTER_STATES::RUN:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : RUN" << endl;
		m_currentState = new State_Character_Run();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;

	case CHARACTER_STATES::JUMP:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : JUMP" << endl;
		m_currentState = new State_Character_Jump();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;

	case CHARACTER_STATES::FLY:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : FLY" << endl;
		m_currentState = new State_Character_Fly();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;

	case LAND:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : LAND" << endl;
		m_currentState = new State_Character_Land();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;
	default:
		return false;
	}
	return true;
}

bool StateMachine_Character::forceChangeState(CHARACTER_STATES newState)
{
	switch (newState)
	{
	case CHARACTER_STATES::STAND :
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the character's state." << endl;
				return false;
			}
			delete(m_currentState);
		}

		cout << "Creating character's state : STAND" << endl;
		m_currentState = new State_Character_Stand();

		if (!m_currentState->initState())
			return false;

		m_stateId = newState;
		return true;

	default : 
		return false;
	}
	return true;
}

CHARACTER_STATES StateMachine_Character::getIdCurrentState()
{
	return m_stateId;
}

State_Character_Base * StateMachine_Character::getCurrentState()
{
	return m_currentState;
}