#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user Clicked mouse down
		{
			processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type) //user released click
		{
			processMouseRelease(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMousePress(sf::Event t_event)
{
	m_firstclick.x = t_event.mouseButton.x;
	m_firstclick.y = t_event.mouseButton.y;
}

void Game::processMouseRelease(sf::Event t_event)
{
	m_secondclick.x = t_event.mouseButton.x;
	m_secondclick.y = t_event.mouseButton.y;
	sf::Vector2f velocity = m_secondclick - m_firstclick;
	float forwardRadians = std::atan2(velocity.y, velocity.x);
	float forwardDegrees = 180.0f * forwardRadians / static_cast<float>(M_PI);
	forwardDegrees += 90;

	m_plane1Velocity = velocity / 100.0f;
	m_plane1Forwards = forwardDegrees;
	m_plane1Sprite.setRotation(forwardDegrees);

}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	movePlanes();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_skySprite);
	m_window.draw(m_plane1Sprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_skyTex.loadFromFile("ASSETS\\IMAGES\\sky.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading sky background" << std::endl;
	}
	m_skyTex.setRepeated(true);
	m_skySprite.setTexture(m_skyTex);
	m_skySprite.setTextureRect(sf::IntRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	sf::IntRect plane1Rect{ 3, 11, 104, 93 };
	sf::Vector2f plane1Start{ 300.0f, 180.0f };

	if (!m_plane1Tex.loadFromFile("ASSETS\\IMAGES\\planes.png"))
	{
		std::cout << "problem loading plane texture" << std::endl;
	}
	m_plane1Sprite.setTexture(m_plane1Tex);
	m_plane1Sprite.setTextureRect(plane1Rect);
	m_plane1Sprite.setOrigin(plane1Rect.width / 2.0f, plane1Rect.height / 2.0f);
	m_plane1Sprite.setPosition(plane1Start);
}

void Game::movePlanes()
{
	m_plane1Location += m_plane1Velocity;
	m_plane1Sprite.setPosition(m_plane1Location);

}
