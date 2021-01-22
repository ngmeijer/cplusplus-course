#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Character.hpp"

class Arena : public Scene
{
public:
	struct ACTION_VALUES {
		int attackDamage = 100;
		int healAmount = 50;
		int headshotDamage = 200;
	};

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
	void checkInput(sf::Event event, sf::Vector2f mousePos, SceneHandler& handler, int& counter);

	void showBattleWonScreen(SceneHandler& handler, int& counter);

	int generateRandomAction();

	//Character import & UI update
	void importCharacter();
	void updateSkills();
	void handleActions(int turn, int action, int damageDealt, int staminaSpent, int healAmount);
	void updateActionText(int turn, int buttonClicked, int damage, int health, std::string enemyName);
	void adjustSkillScaling(ACTION_VALUES values, Character& character, int strength, int heal, int headshot);
	void saveHighScore();
};