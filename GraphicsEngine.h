#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include <iostream>
#include <vector>
#include "CharacterImage.h"
#include "State_Character_Base.h"

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
	void setMap(Map * map);
	Sprite * getCharacterImage();
	bool loadRessource();
	bool loadFont();
	bool loadTexture();
	void emptyObjects();	
	void initTexts();
	void initSprites();
	void setRessource();
	void createShadow(int shadowX, int shadowY, int orientation);
	void setFocusSprite(float x);

	void syncCharacter(int x, int y, int state, int orientation);
	bool collideText(double x, double y);
	void draw();
	void display();	

protected:
	RenderWindow * m_window;
	vector<Font> m_fonts;
	vector<Texture> m_textures;
	View m_view;
	Map * m_map;

	// Sprites
	int m_playerSprite;
	int m_sens;
	vector<Text *> m_texts;
	vector<Sprite *> m_sprites;	
	vector<Sprite *> m_mapSprites;
	Sprite * m_characterSprites;
	bool m_displayShadow;
	Sprite * m_shadow;

	int m_currentState;
	const double SCREEN_WIDTH = 800;
	const double SCREEN_HEIGHT = 600;
};