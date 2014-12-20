#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(RenderWindow * window)
{
	m_window = window;
	m_view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);	

	m_window->setView(m_view);
}

GraphicsEngine::~GraphicsEngine()
{
	emptyObjects();
}

void GraphicsEngine::setCurrentState(GRAPHIC_STATES newState)
{
	m_currentState = newState;
}

void GraphicsEngine::setWindow(RenderWindow * window)
{
	m_window = window;
	m_window->setView(m_view);
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
	Font font;
	if (!font.loadFromFile("./Assets/Fonts/Blackhead.otf"))
	{
		cout << "Error during the loading of the fonts" << endl;
		return false;
	}

	cout << "Fonts successfully loaded" << endl;
	m_fonts.push_back(font);
	return true;
}

void GraphicsEngine::emptyObjects()
{
	m_texts.clear();
	m_sprites.clear();
}

bool GraphicsEngine::loadTexture()
{
	Texture text1, text2;

	if (!text1.loadFromFile("./Assets/Images/menu.jpg"))
	{
		cout << "Error during the loading of the textures (menu.jpg)" << endl;
		return false;
	}

	if (!text2.loadFromFile("./Assets/Images/arrow.png"))
	{
		cout << "Error during the loading of the textures (arrow.png)" << endl;
		return false;
	}

	m_textures.push_back(text1);
	m_textures.push_back(text2);

	cout << "Texture successfully loaded" << endl;
	return true;	
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

	for (it = 0; it < m_sprites.size(); ++it)
	{
		m_window->draw(*m_sprites.at(it));
	}

	for (it = 0; it < m_texts.size(); ++it)
	{
		m_window->draw(*m_texts.at(it));
	}

	display();
}

void GraphicsEngine::display()
{
	//cout << m_fonts.size() << " fonts." << endl;
	//cout << m_textures.size() << " textures" << endl;

	m_window->display();
}