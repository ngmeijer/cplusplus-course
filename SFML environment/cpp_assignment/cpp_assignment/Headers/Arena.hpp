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

	//Generate scene
	void handleBackground();
	void handleButtons();
	void handleTextbox();

	//Input
	void checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter);

	int generateRandomAction();

	//Character import & UI update
	void importCharacter();
	void updateSkills();
	void handleActions(int turn, int action, int damageDealt, int staminaSpent, int healAmount);
	void updateActionText(int buttonClicked, std::string name, int damage, int health, std::string enemyName);

	void adjustSkillScaling(int strength, int agility, int headshot);
};