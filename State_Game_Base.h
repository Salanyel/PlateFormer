#pragma once
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class State_Game_Base
{
public:
	State_Game_Base(RenderWindow * window);
	~State_Game_Base();
	virtual int getStateStatus() = 0;

	virtual bool initState(RenderWindow * window) = 0;
	virtual bool clearState() = 0;
	virtual void operate() = 0;
	virtual void processEvents(Event event) = 0;
	virtual void processEvents() = 0;

protected:
	RenderWindow * m_window;

};

