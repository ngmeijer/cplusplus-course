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
	void handlePlayerText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence);
	void handleEnemyText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence);
	void handleBackground();
	void handleButtons();
	void handleTextbox();

	//Input
	void checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter);

	//Character import & UI update
	void importCharacter(int p_strength, int p_agility, int p_intelligence);
	void updateSkills();
	void handleActions(int turn, int action, int damageDealt, int magicSpent);
	void updateActionText(int buttonClicked, std::string name, int damage, int health);

	//Character UI generation
	void handlePlayer(sf::RectangleShape& health, sf::RectangleShape& stamina, sf::RectangleShape& background, SpriteObject& characterSprite);
	void handleEnemy(sf::RectangleShape& health, sf::RectangleShape& stamina, sf::RectangleShape& background, SpriteObject& characterSprite);

	void adjustSkillScaling(int strength, int agility, int headshot);
};

