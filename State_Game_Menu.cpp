#include "State_Game_Menu.h"

using namespace std;

State_Game_Menu::State_Game_Menu(RenderWindow * window) : State_Game_Base(window)
{
	m_graphics = new GraphicsEngine();
	m_physics = new PhysicsEngine();
}


State_Game_Menu::~State_Game_Menu()
{
}

bool State_Game_Menu::initState(RenderWindow * window)
{
	cout << "Initialising game state : MENU" << endl;

	return true;
}

bool State_Game_Menu::clearState()
{
	delete(m_graphics);
	delete(m_physics);

	return true;
}

void State_Game_Menu::operate()
{

}

void State_Game_Menu::processEvents(Event event)
{

}

void State_Game_Menu::processEvents()
{

}
