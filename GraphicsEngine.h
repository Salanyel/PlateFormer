#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

enum GRAPHIC_STATES
{
	MENU_GRAPHICS,
	GAME_GRAPHICS
};

class GraphicsEngine
{
public:
	GraphicsEngine(RenderWindow * window);
	~GraphicsEngine();

	void setCurrentState(GRAPHIC_STATES newState);
	void setWindow(RenderWindow * window);
	bool loadRessource();
	bool loadFont();
	bool loadTexture();
	void emptyObjects();
	void initTexts();
	void initSprites();
	void setRessource();
	void setFocusSprite(float x);

	bool collideText(double x, double y);
	void draw();
	void display();	

protected:
	RenderWindow * m_window;
	vector<Font> m_fonts;
	vector<Texture> m_textures;
	View m_view;

	// Sprites
	vector<Text *> m_texts;
	vector<Sprite *> m_sprites;	

	int m_currentState;
	const double SCREEN_WIDTH = 800;
	const double SCREEN_HEIGHT = 600;
};