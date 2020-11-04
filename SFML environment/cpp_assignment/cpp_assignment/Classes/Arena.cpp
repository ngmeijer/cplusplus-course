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
Button continueFightButton;

SpriteObject sceneBackground("background", "FightScene.jpg");

sf::RectangleShape playerBackground;
sf::RectangleShape playerHealth;
sf::RectangleShape playerHealthBackground;
sf::RectangleShape playerMagic;
SpriteObject playerSprite("playerSprite", "bulbasaur.png");
SpriteObject playerStrengthSprite("playerStrength", "strengthIcon.png");
SpriteObject playerAgilitySprite("playerAgility", "agilityIcon.png");
SpriteObject playerIntelligenceSprite("playerIntelligence", "intelligenceIcon.png");

sf::RectangleShape enemyBackground;
sf::RectangleShape enemyHealth;
sf::RectangleShape enemyHealthBackground;
sf::RectangleShape enemyMagic;
sf::RectangleShape enemyMagicBackground;
SpriteObject enemySprite("enemySprite", "charmander.png");
SpriteObject enemyStrengthSprite("enemyStrength", "strengthIcon.png");
SpriteObject enemyAgilitySprite("enemyAgility", "agilityIcon.png");
SpriteObject enemyIntelligenceSprite("enemyIntelligence", "intelligenceIcon.png");

sf::Text playerStrengthText;
sf::Text playerAgilityText;
sf::Text playerIntelligenceText;

RectangleShape textBoxBackground;
sf::Text characterActionText;
sf::Text turnText;
std::string currentAction = "THIS IS SPARTA";
std::string turnString = "Your turn!";

sf::Text enemyStrengthText;
sf::Text enemyAgilityText;
sf::Text enemyIntelligenceText;

Character player;
Character enemy;

std::ifstream characterDataArena("PlayerData.txt");
std::vector<int> statsVecArena;

int windowWidth;

enum ACTION_BUTTONS {
	ATTACK,
	PREPARE,
	RECOVER,
	MAGIC,
};

ACTION_BUTTONS selectionAction;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;
	windowWidth = windowRef.getSize().x;

	handleBackground();
	handleTextbox();
	handleButtons();
	handlePlayer(playerHealth, playerMagic, playerBackground, playerSprite);
	handleEnemy(enemyHealth, enemyMagic, enemyBackground, enemySprite);

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

void Arena::handlePlayerText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence) {

	strength.setString(to_string(player.m_strength));
	agility.setString(to_string(player.m_agility));
	intelligence.setString(to_string(player.m_intelligence));

	strength.setFont(m_font);
	agility.setFont(m_font);
	intelligence.setFont(m_font);

	strength.setPosition(70, 200);
	agility.setPosition(240, 200);
	intelligence.setPosition(410, 200);

	strength.setCharacterSize(50);
	agility.setCharacterSize(50);
	intelligence.setCharacterSize(50);

	addTextObject(strength);
	addTextObject(agility);
	addTextObject(intelligence);
}

void Arena::handlePlayer(sf::RectangleShape& health, sf::RectangleShape& magicCapacity, sf::RectangleShape& background, SpriteObject& characterSprite) {
	addRectangleObject(background);
	addSpriteObject(characterSprite);
	addSpriteObject(playerStrengthSprite);
	addSpriteObject(playerAgilitySprite);
	addSpriteObject(playerIntelligenceSprite);
	addRectangleObject(health);
	addRectangleObject(playerHealthBackground);
	addRectangleObject(magicCapacity);

	background.setSize(sf::Vector2f(500, 400));
	background.setPosition(sf::Vector2f(10, 10));
	background.setFillColor(Color(120, 120, 120, 150));

	characterSprite.setPosition(sf::Vector2f(500.0f, 500.0f));
	characterSprite.setScale(sf::Vector2f(5.0f, 5.0f));

	health.setSize(sf::Vector2f(480, 10));
	health.setPosition(sf::Vector2f(20, 330));
	health.setFillColor(Color::Red);

	magicCapacity.setSize(sf::Vector2f(480, 10));
	magicCapacity.setPosition(sf::Vector2f(20, 360));
	magicCapacity.setFillColor(Color::Blue);

	playerStrengthSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	playerAgilitySprite.setScale(sf::Vector2f(0.25f, 0.25f));
	playerIntelligenceSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	playerStrengthSprite.setPosition(sf::Vector2f(20, 75));
	playerAgilitySprite.setPosition(sf::Vector2f(190, 75));
	playerIntelligenceSprite.setPosition(sf::Vector2f(360, 75));

	handlePlayerText(playerStrengthText, playerAgilityText, playerIntelligenceText);
}

void Arena::handleEnemyText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence) {
	strength.setString(to_string(player.m_strength));
	agility.setString(to_string(player.m_agility));
	intelligence.setString(to_string(player.m_intelligence));

	strength.setFont(m_font);
	agility.setFont(m_font);
	intelligence.setFont(m_font);

	strength.setPosition(1490, 200);
	agility.setPosition(1660, 200);
	intelligence.setPosition(1830, 200);

	strength.setCharacterSize(50);
	agility.setCharacterSize(50);
	intelligence.setCharacterSize(50);

	addTextObject(strength);
	addTextObject(agility);
	addTextObject(intelligence);
}

void Arena::handleEnemy(sf::RectangleShape& health, sf::RectangleShape& magicCapacity, sf::RectangleShape& background, SpriteObject& characterSprite) {
	addRectangleObject(background);
	addSpriteObject(enemyStrengthSprite);
	addSpriteObject(enemyAgilitySprite);
	addSpriteObject(enemyIntelligenceSprite);
	addSpriteObject(characterSprite);
	addRectangleObject(enemyHealthBackground);
	addRectangleObject(health);
	addRectangleObject(enemyMagicBackground);
	addRectangleObject(magicCapacity);

	background.setSize(sf::Vector2f(500, 400));
	background.setPosition(sf::Vector2f(1410, 10));
	background.setFillColor(Color(120, 120, 120, 150));

	characterSprite.setPosition(sf::Vector2f(1100.0f, 400.0f));
	characterSprite.setScale(sf::Vector2f(5.0f, 5.0f));

	health.setSize(sf::Vector2f(480, 10));
	health.setPosition(sf::Vector2f(1420, 330));
	health.setFillColor(Color::Red);
	enemyHealthBackground.setSize(sf::Vector2f(480, 10));
	enemyHealthBackground.setPosition(sf::Vector2f(1420, 330));
	enemyHealthBackground.setFillColor(Color(0, 0, 0, 200));

	magicCapacity.setSize(sf::Vector2f(480, 10));
	magicCapacity.setPosition(sf::Vector2f(1420, 360));
	magicCapacity.setFillColor(Color::Blue);
	enemyMagicBackground.setSize(sf::Vector2f(480, 10));
	enemyMagicBackground.setPosition(sf::Vector2f(1420, 360));
	enemyMagicBackground.setFillColor(Color(0, 0, 0, 200));

	enemyStrengthSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	enemyAgilitySprite.setScale(sf::Vector2f(0.25f, 0.25f));
	enemyIntelligenceSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	enemyStrengthSprite.setPosition(sf::Vector2f(1450, 75));
	enemyAgilitySprite.setPosition(sf::Vector2f(1620, 75));
	enemyIntelligenceSprite.setPosition(sf::Vector2f(1790, 75));

	handleEnemyText(enemyStrengthText, enemyAgilityText, enemyIntelligenceText);
}

void Arena::handleTextbox() {
	textBoxBackground.setSize(sf::Vector2f(1600, 160));
	textBoxBackground.setPosition(sf::Vector2f(160, 770));
	textBoxBackground.setFillColor(Color(0, 0, 0, 150));

	addRectangleObject(textBoxBackground);

	characterActionText.setFont(m_font);
	characterActionText.setString(currentAction);
	characterActionText.setPosition(sf::Vector2f(180, 790));
	characterActionText.setCharacterSize(40);

	turnText.setFont(m_font);
	turnText.setString(turnString);
	turnText.setPosition(sf::Vector2f(180, 860));
	turnText.setCharacterSize(40);

	addTextObject(characterActionText);
	addTextObject(turnText);
}

void Arena::handleButtons() {
	attackButton.setSize(sf::Vector2f(200, 60));
	attackButton.setPosition(sf::Vector2f(400, 950));
	attackButton.setColour(Color(255, 0, 0, 120));
	attackButton.setString("Attack", m_font, 40, Color::White);

	prepareButton.setSize(sf::Vector2f(200, 60));
	prepareButton.setPosition(sf::Vector2f(700, 950));
	prepareButton.setColour(Color(125, 125, 125, 120));
	prepareButton.setString("Prepare", m_font, 40, Color::White);

	recoverButton.setSize(sf::Vector2f(200, 60));
	recoverButton.setPosition(sf::Vector2f(1000, 950));
	recoverButton.setColour(Color(0, 255, 0, 120));
	recoverButton.setString("Recover", m_font, 40, Color::White);

	magicButton.setSize(sf::Vector2f(220, 60));
	magicButton.setPosition(sf::Vector2f(1300, 950));
	magicButton.setColour(Color(0, 0, 255, 120));
	magicButton.setString("Cast Magic", m_font, 40, Color::White);

	continueFightButton.setSize(sf::Vector2f(300, 100));
	continueFightButton.setPosition(sf::Vector2f(810, 650));
	continueFightButton.setColour(Color(0, 0, 255, 120));
	continueFightButton.setString("Continue", m_font, 50, Color::Red);

	quitButtonArena.setSize(sf::Vector2f(130, 60));
	quitButtonArena.setPosition(sf::Vector2f(1700, 1000));
	quitButtonArena.setColour(Color::Black);
	quitButtonArena.setString("Quit", m_font, 50, Color::White);

	addGameObject(attackButton);
	addGameObject(prepareButton);
	addGameObject(recoverButton);
	addGameObject(magicButton);
	addGameObject(continueFightButton);
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

			if (attackButton.onClick(mousePos) == true) {
				updateAction(ATTACK, "Bulbasaur", 100, 0);
			}

			if (prepareButton.onClick(mousePos) == true) {
				updateAction(PREPARE, "Bulbasaur", 0, 0);
			}

			if (recoverButton.onClick(mousePos) == true) {
				updateAction(RECOVER, "Bulbasaur", 0, 100);
			}

			if (magicButton.onClick(mousePos) == true) {
				updateAction(MAGIC, "Bulbasaur", 100, 0);
				updateStats(0, MAGIC, 75, 100);
			}

			if (continueFightButton.onClick(mousePos) == true) {

			}
		}
	}
}

void Arena::importCharacter(int p_strength, int p_agility, int p_intelligence)
{
	player.m_strength = p_strength;
	player.m_agility = p_agility;
	player.m_intelligence = p_intelligence;

	updateSkills();
}

void Arena::updateSkills() {
	playerStrengthText.setString(to_string(player.m_strength));
	playerAgilityText.setString(to_string(player.m_agility));
	playerIntelligenceText.setString(to_string(player.m_intelligence));
}

void Arena::updateStats(int turn, int action, int damageDealt, int magicSpent) {
	int enemyHealthLeft = enemyHealth.getSize().x;
	int playerMagicLeft = playerMagic.getSize().x;

	switch (turn) {
		//Player's turn
	case 0:
		if ((enemyHealthLeft - damageDealt >= 0) && (playerMagicLeft - magicSpent >= 0)) {
			enemyHealth.setSize(sf::Vector2f(enemyHealthLeft - damageDealt, 10));
			playerMagic.setSize(sf::Vector2f(playerMagicLeft - magicSpent, 10));

			switch (action) {
			case ATTACK:
				break;
			case PREPARE:
				break;
			}
		}
		break;
		//Enemy's turn
	case 1:
		playerHealth.setSize(sf::Vector2f(playerHealth.getSize().x - damageDealt, 10));
		enemyMagic.setSize(sf::Vector2f(enemyMagic.getSize().x - magicSpent, 10));
		break;
	}
}

void Arena::updateAction(int buttonClicked, std::string characterName, int damageDone, int healthGained) {
	switch (buttonClicked) {
	case ATTACK:
		characterActionText.setString((characterName + " has attacked for: " + to_string(damageDone) + " damage!"));
		break;
	case PREPARE:
		characterActionText.setString((characterName + " is preparing for a powerful next attack!"));
		break;
	case RECOVER:
		characterActionText.setString((characterName + " has healed for: " + to_string(healthGained) + " HP!"));
		break;
	case MAGIC:
		characterActionText.setString((characterName + " has cast a magic spell, dealing: " + to_string(damageDone) + " damage!"));
		break;
	}
}