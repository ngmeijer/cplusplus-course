#include <iostream>

#include "../Headers/Arena.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

Button attackButton;
Button prepareButton;
Button recoverButton;
Button magicButton;
Button quitButtonArena;

RectangleShape playerBackground;
SpriteObject playerStrengthSprite("playerStrength", "strengthIcon.png");
SpriteObject playerAgilitySprite("playerAgility", "agilityIcon.png");
SpriteObject playerIntelligenceSprite("playerIntelligence", "intelligenceIcon.png");

RectangleShape enemyBackground;
SpriteObject enemyStrengthSprite("enemyStrength", "strengthIcon.png");
SpriteObject enemyAgilitySprite("enemyAgility", "agilityIcon.png");
SpriteObject enemyIntelligenceSprite("enemyIntelligence", "intelligenceIcon.png");

Text playerStrengthText;
Text playerAgilityText;
Text playerIntelligenceText;

Text enemyStrengthText;
Text enemyAgilityText;
Text enemyIntelligenceText;

Character player;
Character enemy;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	handleBackground();
	handleButtons();
	handlePlayer(windowRef);
	handleEnemy(windowRef);
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
	addGameObject(playerStrengthSprite);
	addGameObject(playerAgilitySprite);
	addGameObject(playerIntelligenceSprite);

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
	addGameObject(enemyStrengthSprite);
	addGameObject(enemyAgilitySprite);
	addGameObject(enemyIntelligenceSprite);

	enemyStrengthSprite.setScale(sf::Vector2f(0.15f, 0.15f));
	enemyAgilitySprite.setScale(sf::Vector2f(0.15f, 0.15f));
	enemyIntelligenceSprite.setScale(sf::Vector2f(0.15f, 0.15f));

	enemyStrengthSprite.setPosition(sf::Vector2f(1550, 200));
	enemyAgilitySprite.setPosition(sf::Vector2f(1650, 200));
	enemyIntelligenceSprite.setPosition(sf::Vector2f(1750, 200));

	handleEnemyText();
}

void Arena::handleButtons() {
	attackButton.setSize(sf::Vector2f(200, 100));
	attackButton.setPosition(sf::Vector2f(400, 900));
	attackButton.setColour(Color::Transparent);
	attackButton.setString("Attack", m_font, 30, Color::White);

	prepareButton.setSize(sf::Vector2f(200, 100));
	prepareButton.setPosition(sf::Vector2f(700, 900));
	prepareButton.setColour(Color::Transparent);
	prepareButton.setString("Prepare", m_font, 30, Color::White);

	recoverButton.setSize(sf::Vector2f(200, 100));
	recoverButton.setPosition(sf::Vector2f(1000, 900));
	recoverButton.setColour(Color::Transparent);
	recoverButton.setString("Recover", m_font, 30, Color::White);

	magicButton.setSize(sf::Vector2f(200, 100));
	magicButton.setPosition(sf::Vector2f(1300, 900));
	magicButton.setColour(Color::Transparent);
	magicButton.setString("Cast Magic", m_font, 30, Color::White);

	quitButtonArena.setSize(sf::Vector2f(200, 100));
	quitButtonArena.setPosition(sf::Vector2f(1700, 1000));
	quitButtonArena.setColour(Color::Transparent);
	quitButtonArena.setString("Quit", m_font, 50, Color::White);

	addGameObject(attackButton);
	addGameObject(prepareButton);
	addGameObject(recoverButton);
	addGameObject(magicButton);
	addGameObject(quitButtonArena);
}

void Arena::handleBackground() {
	playerBackground.setSize(sf::Vector2f(500, 400));
	playerBackground.setPosition(sf::Vector2f(10, 10));
	playerBackground.setFillColor(Color(120, 0, 0, 100));

	enemyBackground.setSize(sf::Vector2f(500, 400));
	enemyBackground.setPosition(sf::Vector2f(1410, 10));
	enemyBackground.setFillColor(Color(120, 0, 0, 100));

	addRectangleObject(playerBackground);
	addRectangleObject(enemyBackground);
	/*addGameObject(background2);*/
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
