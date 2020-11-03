#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"

class Arena : public Scene
{
private:
	sf::Font m_font;

public:
	Arena();
	Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef);
	~Arena();

	void handlePlayerText();
	void handleEnemyText();
	void handleBackground();
	void handleButtons();
	void checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter);
	void importCharacterStats();
	void handlePlayer(sf::RenderWindow& window);
	void handleEnemy(sf::RenderWindow& window);
};

