#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/Character.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"

class CharScene : public Scene
{
private:
	sf::Font m_font;

public:
	CharScene();
	CharScene(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef);
	~CharScene();

	void handleText(sf::RenderWindow& window);
	void handleBackground();
	void handleButtons();
	void checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter, Character& character);
	void generateCharacter();
	void updateSkillPoints(int valueChange);
};

