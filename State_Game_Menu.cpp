#include "State_Game_Menu.h"

using namespace std;

State_Game_Menu::State_Game_Menu(RenderWindow * window) : State_Game_Base(window)
{
	m_menuFocused = 0;
	m_player = new CXBOXController(1);
	m_graphics = new GraphicsEngine(window);
}

State_Game_Menu::~State_Game_Menu()
{
}

bool State_Game_Menu::initState(RenderWindow * window)
{
	cout << "Initialising game state : MENU" << endl;
	m_graphics->setWindow(m_window);
	m_graphics->setCurrentState(GRAPHIC_STATES::MENU_GRAPHICS);
	if (!m_graphics->loadRessource())
	{
		cout << "Error during the loading of the ressources" << endl;
		return false;
	}

	m_graphics->initTexts();
	m_graphics->initSprites();

	return true;
}

bool State_Game_Menu::clearState()
{
	delete(m_graphics);

	return true;
}

void State_Game_Menu::operate()
{
	m_graphics->draw();
}

void State_Game_Menu::processEvents(Event event)
{
	XINPUT_STATE state;
	state = m_player->GetState();
	Vector2i tmp = Mouse::getPosition(*m_window);
	float ly, magnitude;
	ly = state.Gamepad.sThumbLY;
	magnitude = sqrt(ly * ly + ly * ly);

	if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK))
		m_window->close();

	if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_A|| Mouse::isButtonPressed(Mouse::Left) && m_graphics->collideText(tmp.x, tmp.y) || Event::KeyPressed && event.key.code == Keyboard::Return || Event::KeyPressed && event.key.code == Keyboard::Space)
	{
		if (m_menuFocused == 1)
			m_window->close();
		else
			cout << "Launch the game" << endl;
	}		

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up || state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP || magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && ly > 0)
	{
		m_menuFocused = 0;
		m_graphics->setFocusSprite(m_menuFocused);
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down || state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN || magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && ly < 0)
	{
		m_menuFocused = 1;
		m_graphics->setFocusSprite(m_menuFocused);
	}

}

void State_Game_Menu::processEvents()
{
	Vector2i tmp = Mouse::getPosition(*m_window);
	if (m_graphics->collideText(tmp.x, tmp.y))
	{
		if (tmp.y > m_window->getSize().y / 2)
			m_menuFocused = 1;
		else
			m_menuFocused = 0;

		m_graphics->setRessource();
	}

	
}

GraphicsEngine* State_Game_Menu::getGraphics()
{
	return m_graphics;
}
