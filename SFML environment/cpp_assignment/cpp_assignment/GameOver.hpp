#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"

class GameOver : public Scene
{
private:
	sf::Font m_font;

public:
	GameOver();
	GameOver(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef);
	~GameOver();

	//Generate scene
	void handleBackground();
	void handleButtons();

	//Input
	void checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter);
};

