#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

const int SCREEN_WIDTH = 800u;
const int SCREEN_HEIGHT = 600u;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePress(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void movePlanes();
	void boundaryCheck();
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_plane1Tex;
	sf::Sprite m_plane1Sprite;
	sf::Texture m_skyTex;
	sf::Sprite m_skySprite;
	sf::Vector2f m_firstclick{ 0.0f,0.0f };
	sf::Vector2f m_secondclick{ 0.0f,0.0f };
	sf::Vector2f m_plane1Velocity{ 1.0f, -1.0f };
	float m_plane1Forwards = 45.0f;
	sf::Vector2f m_plane1Location;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP
