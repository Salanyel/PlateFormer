#include "StateMachine_Game.h"

StateMachine_Game::StateMachine_Game(RenderWindow * window) : m_window(window)
{
}

StateMachine_Game::~StateMachine_Game()
{
}

bool StateMachine_Game::changeState(GAME_STATES newState)
{
	switch (newState)
	{
	case GAME_STATES::MENU :
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the state." << endl;
				return false;
			}
			delete(m_currentState);
		}
		cout << "Creating new game state" << endl;
		m_currentState = new State_Game_Menu(m_window);
		cout << "New game state created" << endl;
		
		if (!m_currentState->initState(m_window))
		{
			return false;
		}

		return true;

	default:
		return false;

	}
	cout << "test" << endl;
	return true;
}

void StateMachine_Game::operate()
{
	m_currentState->operate();
}

State_Game_Base * StateMachine_Game::getCurrentState()
{
	return m_currentState;
}