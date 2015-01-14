#include "State_Game_Game.h"

State_Game_Game::State_Game_Game(RenderWindow * window) : State_Game_Base(window)
{
	m_player = new CXBOXController(1);
	m_graphics = new GraphicsEngine(window);
	m_physics = new PhysicsEngine(window, m_graphics);
}

State_Game_Game::~State_Game_Game()
{
}

int State_Game_Game::getStateStatus()
{

	return STATE_CHANGE;
}

bool State_Game_Game::initState(RenderWindow * window)
{
	cout << "Initialising game state : GAME" << endl;
	m_graphics->setWindow(m_window);
	m_graphics->setCurrentState(GRAPHIC_STATES::GAME_GRAPHICS);
	if (!m_graphics->loadRessource())
	{
		cout << "Error during the loading of the ressources" << endl;
		return false;
	}

	m_physics->setWindow(m_window);
	m_physics->setCurrentState(PHYSIC_STATES::GAME_PHYSICS);

	if (!m_physics->initEngine())
	{
		cout << "Error during the loading of the physics engine" << endl;
		return false;
	}
	m_graphics->setMap(m_physics->getMap());
	m_graphics->initTexts();
	m_graphics->initSprites();

	m_physics->setCharacter();

	return true;
}

bool State_Game_Game::clearState()
{
	delete(m_graphics);
	delete(m_physics);
	delete(m_player);

	return true;
}

void State_Game_Game::operate()
{
	m_graphics->draw();
}

void State_Game_Game::processEvents(Event event)
{
	XINPUT_STATE state = m_player->GetState();
	if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK))
		m_window->close();
	else
		m_physics->getCharacter()->processEvents(event);
}

void State_Game_Game::processEvents()
{
	m_physics->getCharacter()->processEvents();
}

GraphicsEngine * State_Game_Game::getGraphics()
{
	return m_graphics;
}

PhysicsEngine * State_Game_Game::getPhysics()
{
	return m_physics;
}