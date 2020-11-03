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
	CharScene(std::string identifier, sf::Font& fontRef);
	~CharScene();

	void handleText();
	void handleBackground();
	void handleButtons();
	void checkInput(sf::Event event, sf::Vector2f mousePos, SceneHandler& handler, int& counter);
	void generateCharacter();
	void updateSkillPoints(int valueChange);
	void updateStats();
	void writeCharacterToFile();
	void importCharacter(int strength, int agility, int intelligence, int availablePoints);
};

