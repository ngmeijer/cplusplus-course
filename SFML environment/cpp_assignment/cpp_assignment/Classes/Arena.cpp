#include <iostream>
#include <fstream>

#include "../Headers/Arena.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

Button attackButton;
Button prepareButton;
Button recoverButton;
Button magicButton;
Button quitButtonArena;

SpriteObject sceneBackground("background", "FightScene.jpg");

sf::RectangleShape playerBackground;
sf::RectangleShape playerHealth;
sf::RectangleShape playerStamina;
SpriteObject playerSprite("playerSprite", "bulbasaur.png");
SpriteObject playerStrengthSprite("playerStrength", "strengthIcon.png");
SpriteObject playerAgilitySprite("playerAgility", "agilityIcon.png");
SpriteObject playerIntelligenceSprite("playerIntelligence", "intelligenceIcon.png");

sf::RectangleShape enemyBackground;
sf::RectangleShape enemyHealth;
sf::RectangleShape enemyStamina;
SpriteObject enemySprite("enemySprite", "charmander.png");
SpriteObject enemyStrengthSprite("enemyStrength", "strengthIcon.png");
SpriteObject enemyAgilitySprite("enemyAgility", "agilityIcon.png");
SpriteObject enemyIntelligenceSprite("enemyIntelligence", "intelligenceIcon.png");

Text playerStrengthText;
Text playerAgilityText;
Text playerIntelligenceText;

sf::Text enemyStrengthText;
sf::Text enemyAgilityText;
sf::Text enemyIntelligenceText;

Character player;
Character enemy;

std::ifstream characterDataArena("PlayerData.txt");
std::vector<int> statsVecArena;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	handleBackground();
	handleButtons();
	handlePlayer(windowRef);
	handleEnemy(windowRef);

	if (characterDataArena.fail()) {
		std::cout << "\n" << "Failed opening the PlayerData.txt file." << endl << "\n";
	}
	else {
		string line;
		while (getline(characterDataArena, line)) {
			statsVecArena.push_back(std::stoi(line));
		}
		characterDataArena.close();
	}

	player.m_strength = statsVecArena[0];
	player.m_agility = statsVecArena[1];
	player.m_intelligence = statsVecArena[2];
}

Arena::~Arena() { }

void Arena::handlePlayerText() {

	playerStrengthText.setString(to_string(player.m_strength));
	playerAgilityText.setString(to_string(player.m_agility));
	playerIntelligenceText.setString(to_string(player.m_intelligence));

	playerIntelligenceText.setFont(m_font);
	playerAgilityText.setFont(m_font);
	playerStrengthText.setFont(m_font);

	playerStrengthText.setPosition(100, 300);
	playerAgilityText.setPosition(200, 300);
	playerIntelligenceText.setPosition(300, 300);

	addTextObject(playerStrengthText);
	addTextObject(playerAgilityText);
	addTextObject(playerIntelligenceText);
}

void Arena::handlePlayer(RenderWindow& window) {
	addRectangleObject(playerBackground);
	addSpriteObject(playerSprite);
	addSpriteObject(playerStrengthSprite);
	addSpriteObject(playerAgilitySprite);
	addSpriteObject(playerIntelligenceSprite);
	addRectangleObject(playerHealth);
	addRectangleObject(playerStamina);

	playerBackground.setSize(sf::Vector2f(500, 400));
	playerBackground.setPosition(sf::Vector2f(10, 10));
	playerBackground.setFillColor(Color(120, 120, 120, 150));

	playerSprite.setPosition(sf::Vector2f(500.0f, 500.0f));
	playerSprite.setScale(sf::Vector2f(5.0f, 5.0f));

	playerHealth.setSize(sf::Vector2f(480, 10));
	playerHealth.setPosition(sf::Vector2f(20, 50));
	playerHealth.setFillColor(Color::Red);

	playerStamina.setSize(sf::Vector2f(480, 10));
	playerStamina.setPosition(sf::Vector2f(20, 80));
	playerStamina.setFillColor(Color::Blue);

	playerStrengthSprite.setScale(sf::Vector2f(0.15f, 0.15f));
	playerAgilitySprite.setScale(sf::Vector2f(0.15f, 0.15f));
	playerIntelligenceSprite.setScale(sf::Vector2f(0.15f, 0.15f));

	playerStrengthSprite.setPosition(sf::Vector2f(90, 200));
	playerAgilitySprite.setPosition(sf::Vector2f(190, 200));
	playerIntelligenceSprite.setPosition(sf::Vector2f(290, 200));

	handlePlayerText();
}

void Arena::handleEnemyText() {
	enemyStrengthText.setString(to_string(enemy.m_strength));
	enemyAgilityText.setString(to_string(enemy.m_agility));
	enemyIntelligenceText.setString(to_string(enemy.m_intelligence));

	enemyStrengthText.setFont(m_font);
	enemyAgilityText.setFont(m_font);
	enemyIntelligenceText.setFont(m_font);

	enemyStrengthText.setPosition(1560, 300);
	enemyAgilityText.setPosition(1660, 300);
	enemyIntelligenceText.setPosition(1760, 300);

	addTextObject(enemyStrengthText);
	addTextObject(enemyAgilityText);
	addTextObject(enemyIntelligenceText);
}

void Arena::handleEnemy(RenderWindow& window) {
	addRectangleObject(enemyBackground);
	addSpriteObject(enemyStrengthSprite);
	addSpriteObject(enemyAgilitySprite);
	addSpriteObject(enemyIntelligenceSprite);
	addSpriteObject(enemySprite);
	addRectangleObject(enemyHealth);
	addRectangleObject(enemyStamina);

	enemyBackground.setSize(sf::Vector2f(500, 400));
	enemyBackground.setPosition(sf::Vector2f(1410, 10));
	enemyBackground.setFillColor(Color(120, 120, 120, 150));

	enemySprite.setPosition(sf::Vector2f(1100.0f, 400.0f));
	enemySprite.setScale(sf::Vector2f(5.0f, 5.0f));

	enemyHealth.setSize(sf::Vector2f(480, 10));
	enemyHealth.setPosition(sf::Vector2f(1420, 50));
	enemyHealth.setFillColor(Color::Red);

	enemyStamina.setSize(sf::Vector2f(480, 10));
	enemyStamina.setPosition(sf::Vector2f(1420, 80));
	enemyStamina.setFillColor(Color::Blue);

	enemyStrengthSprite.setScale(sf::Vector2f(0.15f, 0.15f));
	enemyAgilitySprite.setScale(sf::Vector2f(0.15f, 0.15f));
	enemyIntelligenceSprite.setScale(sf::Vector2f(0.15f, 0.15f));

	enemyStrengthSprite.setPosition(sf::Vector2f(1550, 200));
	enemyAgilitySprite.setPosition(sf::Vector2f(1650, 200));
	enemyIntelligenceSprite.setPosition(sf::Vector2f(1750, 200));

	handleEnemyText();
}

void Arena::handleButtons() {
	attackButton.setSize(sf::Vector2f(200, 60));
	attackButton.setPosition(sf::Vector2f(400, 900));
	attackButton.setColour(Color(255, 0, 0, 120));
	attackButton.setString("Attack", m_font, 40, Color::White);

	prepareButton.setSize(sf::Vector2f(200, 60));
	prepareButton.setPosition(sf::Vector2f(700, 900));
	prepareButton.setColour(Color(125, 125, 125, 120));
	prepareButton.setString("Prepare", m_font, 40, Color::White);

	recoverButton.setSize(sf::Vector2f(200, 60));
	recoverButton.setPosition(sf::Vector2f(1000, 900));
	recoverButton.setColour(Color(0, 255, 0, 120));
	recoverButton.setString("Recover", m_font, 40, Color::White);

	magicButton.setSize(sf::Vector2f(220, 60));
	magicButton.setPosition(sf::Vector2f(1300, 900));
	magicButton.setColour(Color(0, 0, 255, 120));
	magicButton.setString("Cast Magic", m_font, 40, Color::White);

	quitButtonArena.setSize(sf::Vector2f(130, 60));
	quitButtonArena.setPosition(sf::Vector2f(1700, 1000));
	quitButtonArena.setColour(Color::Black);
	quitButtonArena.setString("Quit", m_font, 50, Color::White);

	addGameObject(attackButton);
	addGameObject(prepareButton);
	addGameObject(recoverButton);
	addGameObject(magicButton);
	addGameObject(quitButtonArena);
}

void Arena::handleBackground() {
	addGameObject(sceneBackground);
}

void Arena::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (quitButtonArena.onClick(mousePos) == true) {
				handler.stackScene("menu");
				counter = 0;
			}
		}
	}
}

void Arena::importCharacter(int p_strength, int p_agility, int p_intelligence)
{
	player.m_strength = p_strength;
	player.m_agility = p_agility;
	player.m_intelligence = p_intelligence;

	updateStats();
}

void Arena::updateStats() {
	playerStrengthText.setString(to_string(player.m_strength));
	playerAgilityText.setString(to_string(player.m_agility));
	playerIntelligenceText.setString(to_string(player.m_intelligence));
}
