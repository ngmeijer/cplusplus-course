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
sf::RectangleShape playerStamina;
SpriteObject playerSprite("playerSprite", "DoomSlayer.png");
SpriteObject playerStrengthSprite("playerStrength", "strengthIcon.png");
SpriteObject playerAgilitySprite("playerAgility", "agilityIcon.png");
SpriteObject playerIntelligenceSprite("playerIntelligence", "intelligenceIcon.png");

sf::RectangleShape enemyBackground;
sf::RectangleShape enemyHealth;
sf::RectangleShape enemyHealthBackground;
sf::RectangleShape enemyMagic;
sf::RectangleShape enemyMagicBackground;
SpriteObject enemySprite("enemySprite", "Zombie.png");
SpriteObject enemyStrengthSprite("enemyStrength", "strengthIcon.png");
SpriteObject enemyAgilitySprite("enemyAgility", "agilityIcon.png");
SpriteObject enemyIntelligenceSprite("enemyIntelligence", "intelligenceIcon.png");

sf::Text playerStrengthText;
sf::Text playerAgilityText;
sf::Text playerIntelligenceText;

RectangleShape textBoxBackground;
sf::Text characterActionText;
sf::Text turnText;
std::string currentAction = "DOOMSLAYER attacked for 50 damage";
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
	HEAL,
	HEADSHOT,
};

struct ACTION_VALUES {
	int attackDamage = 50;
	int healAmount = 50;
	int headshotDamage = 200;
};

ACTION_BUTTONS selectionAction;
ACTION_VALUES actionValues;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;
	windowWidth = windowRef.getSize().x;

	adjustSkillScaling(player.m_strength, player.m_intelligence, player.m_headshot);
	handleBackground();
	handleTextbox();
	handleButtons();
	handlePlayer(playerHealth, playerStamina, playerBackground, playerSprite);
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
	player.m_intelligence = statsVecArena[1];
	player.m_headshot = statsVecArena[2];
}

Arena::~Arena() { }

void Arena::handlePlayerText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence) {

	strength.setString(to_string(player.m_strength));
	agility.setString(to_string(player.m_intelligence));
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

	characterSprite.setPosition(sf::Vector2f(400.0f, 550.0f));
	characterSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	health.setSize(sf::Vector2f(480, 10));
	health.setPosition(sf::Vector2f(20, 330));
	health.setFillColor(Color::Red);

	magicCapacity.setSize(sf::Vector2f(480, 10));
	magicCapacity.setPosition(sf::Vector2f(20, 360));
	magicCapacity.setFillColor(Color::Blue);

	playerStrengthSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	playerAgilitySprite.setScale(sf::Vector2f(1.0f, 1.0f));
	playerIntelligenceSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	playerStrengthSprite.setPosition(sf::Vector2f(20, 75));
	playerAgilitySprite.setPosition(sf::Vector2f(190, 75));
	playerIntelligenceSprite.setPosition(sf::Vector2f(360, 75));

	handlePlayerText(playerStrengthText, playerAgilityText, playerIntelligenceText);
}

void Arena::handleEnemyText(sf::Text& strength, sf::Text& agility, sf::Text& intelligence) {
	strength.setString(to_string(player.m_strength));
	agility.setString(to_string(player.m_intelligence));
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

	characterSprite.setPosition(sf::Vector2f(1100.0f, 710.0f));
	characterSprite.setScale(sf::Vector2f(0.5f, 0.5f));

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

	enemyStrengthSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	enemyAgilitySprite.setScale(sf::Vector2f(1.0f, 1.0f));
	enemyIntelligenceSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	enemyStrengthSprite.setPosition(sf::Vector2f(1415, 75));
	enemyAgilitySprite.setPosition(sf::Vector2f(1585, 75));
	enemyIntelligenceSprite.setPosition(sf::Vector2f(1755, 75));

	handleEnemyText(enemyStrengthText, enemyAgilityText, enemyIntelligenceText);
}

void Arena::handleTextbox() {
	textBoxBackground.setSize(sf::Vector2f(880, 160));
	textBoxBackground.setPosition(sf::Vector2f(520, 20));
	textBoxBackground.setFillColor(Color(0, 0, 0, 150));

	addRectangleObject(textBoxBackground);

	characterActionText.setFont(m_font);
	characterActionText.setString(currentAction);
	characterActionText.setPosition(sf::Vector2f(525, 40));
	characterActionText.setCharacterSize(38);

	turnText.setFont(m_font);
	turnText.setString(turnString);
	turnText.setPosition(sf::Vector2f(525, 100));
	turnText.setCharacterSize(40);

	addTextObject(characterActionText);
	addTextObject(turnText);
}

void Arena::handleButtons() {
	attackButton.setSize(sf::Vector2f(190, 60));
	attackButton.setPosition(sf::Vector2f(520, 250));
	attackButton.setColour(Color(255, 0, 0, 120));
	attackButton.setString("Attack", m_font, 40, Color::White);

	prepareButton.setSize(sf::Vector2f(190, 60));
	prepareButton.setPosition(sf::Vector2f(730, 250));
	prepareButton.setColour(Color(125, 125, 125, 120));
	prepareButton.setString("Prepare", m_font, 40, Color::White);

	recoverButton.setSize(sf::Vector2f(190, 60));
	recoverButton.setPosition(sf::Vector2f(950, 250));
	recoverButton.setColour(Color(0, 255, 0, 120));
	recoverButton.setString("Recover", m_font, 40, Color::White);

	magicButton.setSize(sf::Vector2f(210, 60));
	magicButton.setPosition(sf::Vector2f(1190, 250));
	magicButton.setColour(Color(0, 0, 255, 120));
	magicButton.setString("Headshot", m_font, 40, Color::White);

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
				updateActionText(ATTACK, "DOOMSLAYER", 100, 0);
			}

			if (prepareButton.onClick(mousePos) == true) {
				updateActionText(PREPARE, "DOOMSLAYER", 0, 0);
			}

			if (recoverButton.onClick(mousePos) == true) {
				updateActionText(HEAL, "DOOMSLAYER", 0, 100);
			}

			if (magicButton.onClick(mousePos) == true) {
				updateActionText(HEADSHOT, "DOOMSLAYER", 100, 0);
				handleActions(0, HEADSHOT, 75, 100);
			}

			if (continueFightButton.onClick(mousePos) == true) {

			}
		}
	}
}

void Arena::importCharacter(int p_strength, int p_agility, int p_intelligence)
{
	player.m_strength = p_strength;
	player.m_intelligence = p_agility;
	player.m_intelligence = p_intelligence;

	updateSkills();
}

void Arena::updateSkills() {
	playerStrengthText.setString(to_string(player.m_strength));
	playerAgilityText.setString(to_string(player.m_intelligence));
	playerIntelligenceText.setString(to_string(player.m_intelligence));
}

void Arena::handleActions(int turn, int action, int damageDealt, int staminaSpent) {
	int enemyHealthLeft = enemyHealth.getSize().x;
	int playerStaminaSpent = playerStamina.getSize().x;

	switch (turn) {
	case 0:
		//Player's turn
		switch (action) {
		case ATTACK:
			if (enemyHealthLeft - damageDealt >= 0) {
				enemyHealth.setSize(sf::Vector2f(enemyHealthLeft - damageDealt, 10));
				break;
			}
		case PREPARE:
			break;
		case HEAL:
			if (playerStaminaSpent - staminaSpent >= 0) {
				playerHealth.setSize(sf::Vector2f(480, 10));
				playerStamina.setSize(sf::Vector2f(playerStaminaSpent - staminaSpent, 10));
			}
			break;
		case HEADSHOT:
			if ((enemyHealthLeft - damageDealt >= 0) && (playerStaminaSpent - staminaSpent >= 0)) {

				enemyHealth.setSize(sf::Vector2f(enemyHealthLeft - damageDealt, 10));
				playerStamina.setSize(sf::Vector2f(playerStaminaSpent - staminaSpent, 10));
				break;
			}
			break;
		}
	case 1:
		//Enemy's turn
		switch (action) {
		case ATTACK:
			break;
		case PREPARE:
			break;
		case HEAL:
			break;
		case HEADSHOT:
			break;
		}
	}
}

void Arena::updateActionText(int buttonClicked, std::string characterName, int damageDone, int healthGained) {
	switch (buttonClicked) {
	case ATTACK:
		characterActionText.setString((characterName + " has attacked for: " + to_string(damageDone) + " damage!"));
		break;
	case PREPARE:
		characterActionText.setString((characterName + " has prepared for a powerful next attack!"));
		break;
	case HEAL:
		characterActionText.setString((characterName + " has healed for: " + to_string(healthGained) + " HP!"));
		break;
	case HEADSHOT:
		characterActionText.setString((characterName + " has dealt " + to_string(damageDone) + " headshot damage!"));
		break;
	}
}

void Arena::adjustSkillScaling(int strength, int heal, int headshot) {
	switch (strength) {
	case 3:
		actionValues.attackDamage = player.strengthValues.strength3;
		break;
	case 4:
		actionValues.attackDamage = player.strengthValues.strength4;
		break;
	case 5:
		actionValues.attackDamage = player.strengthValues.strength5;
		break;
	case 6:
		actionValues.attackDamage = player.strengthValues.strength6;
		break;
	case 7:
		actionValues.attackDamage = player.strengthValues.strength7;
		break;
	case 8:
		actionValues.attackDamage = player.strengthValues.strength8;
		break;
	case 9:
		actionValues.attackDamage = player.strengthValues.strength9;
		break;
	case 10:
		actionValues.attackDamage = player.strengthValues.strength10;
		break;
	}

	switch (heal) {
	case 3:
		actionValues.healAmount = player.healValues.heal3;
		break;
	case 4:
		actionValues.healAmount = player.healValues.heal4;
		break;
	case 5:
		actionValues.healAmount = player.healValues.heal5;
		break;
	case 6:
		actionValues.healAmount = player.healValues.heal6;
		break;
	case 7:
		actionValues.healAmount = player.healValues.heal7;
		break;
	case 8:
		actionValues.healAmount = player.healValues.heal8;
		break;
	case 9:
		actionValues.healAmount = player.healValues.heal9;
		break;
	case 10:
		actionValues.healAmount = player.healValues.heal10;
		break;
	}

	switch (headshot) {
	case 3:
		actionValues.headshotDamage = player.headshotValues.headshot3;
		break;
	case 4:
		actionValues.headshotDamage = player.headshotValues.headshot4;
		break;
	case 5:
		actionValues.headshotDamage = player.headshotValues.headshot5;
		break;
	case 6:
		actionValues.headshotDamage = player.headshotValues.headshot6;
		break;
	case 7:
		actionValues.headshotDamage = player.headshotValues.headshot7;
		break;
	case 8:
		actionValues.headshotDamage = player.headshotValues.headshot8;
		break;
	case 9:
		actionValues.headshotDamage = player.headshotValues.headshot9;
		break;
	case 10:
		actionValues.headshotDamage = player.headshotValues.headshot10;
		break;
	}
}