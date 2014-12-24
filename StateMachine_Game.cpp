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
		cout << "Creating new game_menu state" << endl;
		m_currentState = new State_Game_Menu(m_window);
		cout << "New game_menu state created" << endl;
		
		if (!m_currentState->initState(m_window))
		{
			return false;
		}

		return true;

	case GAME_STATES::GAME:
		if (m_currentState != NULL)
		{
			if (!m_currentState->clearState())
			{
				cout << "Error during the cleaning of the state." << endl;
				return false;
			}
			delete(m_currentState);
		}
		cout << "Creating new game_game state" << endl;
		m_currentState = new State_Game_Game(m_window);
		cout << "New game_game state created" << endl;

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

bool StateMachine_Game::operate()
{
	switch (m_currentState->getStateStatus())
	{
	case 0 :
		m_currentState->operate();
		break;

	case 1 :
		if (!changeState(GAME))
			return false;
		break;
	}

	return true;
}

State_Game_Base * StateMachine_Game::getCurrentState()
{
	return m_currentState;
}