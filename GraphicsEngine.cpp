#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(RenderWindow * window)
{
	m_window = window;	
	m_view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_window->setView(m_view);
	m_displayShadow = false;
}

GraphicsEngine::~GraphicsEngine()
{
	emptyObjects();
	delete(m_map);
	delete(m_shadow);
	delete(m_characterSprites);
}

void GraphicsEngine::setCurrentState(GRAPHIC_STATES newState)
{
	m_currentState = newState;

	switch (m_currentState)
	{
	case MENU_GRAPHICS:
		m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	case GAME_GRAPHICS:
		m_view.setSize(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	default:
		break;
	}
}

void GraphicsEngine::setWindow(RenderWindow * window)
{
	m_window = window;
	m_window->setView(m_view);
}

void GraphicsEngine::setMap(Map * map)
{
	m_map = map;
}

Sprite * GraphicsEngine::getCharacterImage()
{
	return m_characterSprites;
}

bool GraphicsEngine::loadRessource()
{
	bool ctrl1, ctrl2;

	ctrl1 = loadFont();
	ctrl2 = loadTexture();

	if (!ctrl1 || !ctrl2)
		return false;
	else
		return true;
}

bool GraphicsEngine::loadFont()
{
	Font * font = new Font();

	switch (m_currentState)
	{
	case MENU_GRAPHICS:
		if (!font->loadFromFile("./Assets/Fonts/Blackhead.otf"))
		{
			cout << "Error during the loading of the fonts" << endl;
			return false;
		}

		cout << "Fonts successfully loaded" << endl;
		m_fonts.push_back(*font);
		return true;

	case GAME_GRAPHICS:
		return true;

	default:
		return false;
	}	
}

void GraphicsEngine::emptyObjects()
{
	m_texts.clear();
	m_sprites.clear();
}

bool GraphicsEngine::loadTexture()
{
	Texture * text = new Texture();

	switch (m_currentState)
	{
	case MENU_GRAPHICS:		

		if (!text->loadFromFile("./Assets/Images/menu.jpg"))
		{
			cout << "Error during the loading of the textures (menu.jpg)" << endl;
			return false;
		}

		m_textures.push_back(*text);

		if (!text->loadFromFile("./Assets/Images/arrow.png"))
		{
			cout << "Error during the loading of the textures (arrow.png)" << endl;
			return false;
		}
		
		m_textures.push_back(*text);

		cout << "Texture successfully loaded" << endl;
		return true;

	case GAME_GRAPHICS:
		if (!text->loadFromFile("./Assets/Images/sheet_character.png"))
		{
			cout << "Error during the loading of the textures (sheet_character.png)" << endl;
			return false;
		}

		m_textures.push_back(*text);

		if (!text->loadFromFile("./Assets/Images/texture.png"))
		{
			cout << "Error during the loading of the textures (texture.png)" << endl;
			return false;
		}

		m_textures.push_back(*text);

		if (!text->loadFromFile("./Assets/Images/Shadow.png"))
		{
			cout << "Error during the loading of the textures (Shadow.png)" << endl;
			return false;
		}

		m_textures.push_back(*text);
		return true;

	default:
		return false;
	}
		
}

void GraphicsEngine::initTexts()
{
	switch (m_currentState)
	{
	case GRAPHIC_STATES::MENU_GRAPHICS:
		int x;
		int y;
		Text * text;

		text = new Text();
		text->setFont(m_fonts.at(0));
		text->setString("Begin the game");
		text->setCharacterSize(24);
		text->setColor(Color::Blue);
		x = SCREEN_WIDTH / 2 - text->getLocalBounds().width / 2;
		y = SCREEN_HEIGHT / 2 - text->getLocalBounds().height * 1.5;
		text->setPosition(x, y);
		m_texts.push_back(text);

		text = new Text();
		text->setFont(m_fonts.at(0));
		text->setString("Exit the game");
		text->setCharacterSize(24);
		text->setColor(Color::Blue);
		x = SCREEN_WIDTH / 2 - text->getLocalBounds().width / 2;
		y = SCREEN_HEIGHT / 2 + text->getLocalBounds().height * 1.5;		
		text->setPosition(x, y);
		m_texts.push_back(text);
	default:
		return;
	}	
}

void GraphicsEngine::initSprites()
{
	switch (m_currentState)
	{
	case GRAPHIC_STATES::MENU_GRAPHICS:
		double scaleX;
		double scaleY;
		Sprite * sprite1, *sprite2;
		Text * text;

		text = m_texts.at(0);
		sprite1 = new Sprite();
		sprite2 = new Sprite();

		sprite1->setTexture(m_textures.at(0));
		sprite1->setPosition(0, 0);
		scaleX = SCREEN_WIDTH / sprite1->getLocalBounds().width;
		scaleY = SCREEN_HEIGHT / sprite1->getLocalBounds().height;
		sprite1->setScale(scaleX, scaleY);
		
		sprite2->setTexture(m_textures.at(1));
		sprite2->setPosition(text->getPosition().x - 50, text->getPosition().y + (text->getGlobalBounds().height - sprite2->getGlobalBounds().height) / 2);

		m_sprites.push_back(sprite1);
		m_sprites.push_back(sprite2);
		break;

	case GAME_GRAPHICS:
		int it;		
		int mapWidth;
		mapWidth = m_map->getMapWidth();
		TILE_TYPE type;
		Sprite * sprite;		
		
		m_characterSprites = new Sprite();
		m_characterSprites->setTexture(m_textures.at(0));
		m_characterSprites->setTextureRect(IntRect(28, 34, 83, 141));

		for (it = 0; it < m_map->getTileNumber(); ++it)
		{
			if (it == 63)
				cout << "temp" << endl;
			sprite = new Sprite();
			sprite->setTexture(m_textures.at(1));			
			type = m_map->getTile(it)->getType();

			switch (type)
			{
			case T_EMPTY:
				sprite->setTextureRect(IntRect(0, 0, 64, 64));
				break;

			case T_BLOCK:
				sprite->setTextureRect(IntRect(65, 0, 64, 64));
				break;

			case T_MAPWALL:
				sprite->setTextureRect(IntRect(129, 0, 64, 64));
				break;

			case T_SPAWN:
				m_sens = 1;
				sprite->setTextureRect(IntRect(0, 0, 64, 64));
				cout << "Center view : " << 64 * (it%mapWidth) + 32 << " x " <<  64 * (it / mapWidth) + 32 << endl;												
				m_characterSprites->setPosition(Vector2f(64 * (it%mapWidth), 64 * (it / mapWidth)));
				m_characterSprites->scale(0.46, 0.46);
				m_view.setCenter(64 * (it%mapWidth) + 32, 64 * (it / mapWidth) + 32);
				m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
				m_window->setView(m_view);
				break;

			default:
				break;
			}			
			sprite->setPosition(64 * (it%mapWidth), 64 * (it/mapWidth));			
			m_mapSprites.push_back(sprite);
		}	
		m_shadow = new Sprite();
		m_shadow->setTexture(m_textures.back());
		m_shadow->setScale(0.51, 0.44);
		break;

	default:
		return;
	}
}

void GraphicsEngine::setRessource()
{
	Sprite * sprite;
	Text * text, * text2;

	switch (m_currentState)
	{
	case GRAPHIC_STATES::MENU_GRAPHICS:
		sprite = m_sprites.at(1);
		text = m_texts.at(0);
		text2 = m_texts.at(1);

		if (text->getPosition().y < Mouse::getPosition(*m_window).y && Mouse::getPosition(*m_window).y < text->getPosition().y + text->getLocalBounds().height)
		{
			sprite->setPosition(sprite->getPosition().x, text->getPosition().y + (text->getLocalBounds().height - sprite->getLocalBounds().height) / 2);
		} else {
			sprite->setPosition(sprite->getPosition().x, text2->getPosition().y + (text2->getLocalBounds().height - sprite->getLocalBounds().height) / 2);
		}
	}
}

void GraphicsEngine::createShadow(int shadowX, int shadowY, int orientation)
{
	m_shadow->setPosition(Vector2f(shadowX, shadowY));
	if (orientation == -1)
		m_shadow->setTextureRect(IntRect(126, 0, -126, 144));
	else
		m_shadow->setTextureRect(IntRect(0, 0, 126, 144));
	m_displayShadow = 1;
}

void GraphicsEngine::setFocusSprite(float x)
{
	switch (m_currentState)
	{
		case GRAPHIC_STATES::MENU_GRAPHICS:
			Text * text;
			Sprite * sprite;
			text = m_texts.at(x);
			sprite = m_sprites.at(1);
			sprite->setPosition(sprite->getPosition().x, text->getPosition().y + (text->getLocalBounds().height - sprite->getLocalBounds().height) / 2);
	}
}

void GraphicsEngine::syncCharacter(int x, int y, int state, int orientation)
{
	int top;
	int left;
	switch (state)
	{
	case STAND :
		if (orientation == 1)
		{
			m_characterSprites->setTextureRect(IntRect(28, 36, orientation * 83, 137));
		}
		else
		{
			m_characterSprites->setTextureRect(IntRect(111, 36, orientation * 83, 137));
		}
		break;

	case RUN:
		if (orientation == 1)
		{
			m_characterSprites->setTextureRect(IntRect(154, 214, orientation * 122, 137));
		}
		else
		{
			m_characterSprites->setTextureRect(IntRect(276, 214, orientation * 122, 137));
		}
		break;

	case JUMP :
		if (orientation == 1)
		{
			m_characterSprites->setTextureRect(IntRect(492, 875, orientation * 105, 137));
		}
		else
		{
			m_characterSprites->setTextureRect(IntRect(597, 875, orientation * 105, 137));
		}
		break;
			
	case FLY :
		if (orientation == 1)
		{
			m_characterSprites->setTextureRect(IntRect(1223, 373, orientation * 101, 137));
		}
		else
		{
			m_characterSprites->setTextureRect(IntRect(1324, 373, orientation * 101, 137));
		}
		break;
	
	default:
		break;
	}

	m_characterSprites->setPosition(Vector2f(x, y));	
}

bool GraphicsEngine::collideText(double x, double y)
{
	int it;
	Text * text;

	for (it = 0; it < m_sprites.size(); ++it)
	{
		text = m_texts.at(it);
		if (x > text->getPosition().x
			&& x < text->getPosition().x + text->getGlobalBounds().width
			&& y > text->getPosition().y
			&& y < text->getPosition().y + text->getGlobalBounds().height)
		{			
			return true;
		}
	}
	return false;
}

void GraphicsEngine::draw()
{
	int it;

	m_window->clear();	

	for (it = 0; it < m_mapSprites.size(); ++it)
	{
		m_window->draw(*m_mapSprites.at(it));
	}

	for (it = 0; it < m_sprites.size(); ++it)
	{
		m_window->draw(*m_sprites.at(it));
	}

	for (it = 0; it < m_texts.size(); ++it)
	{
		m_window->draw(*m_texts.at(it));
	}

	if (m_currentState == GAME_GRAPHICS)
	{		
		if (m_displayShadow)
			m_window->draw(*m_shadow);
		m_window->draw(*m_characterSprites);
		display();
		m_view.setCenter(m_characterSprites->getGlobalBounds().left + m_characterSprites->getGlobalBounds().width / 2, m_characterSprites->getGlobalBounds().top + m_characterSprites->getGlobalBounds().height / 2);
		m_window->setView(m_view);
	}	
	else
		display();
}

void GraphicsEngine::display()
{
	m_window->display();
}