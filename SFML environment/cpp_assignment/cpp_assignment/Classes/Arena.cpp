#include <iostream>
#include <fstream>

#include "../Headers/Arena.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Player.hpp"
#include "../Headers/Enemy.hpp"

Button attackButton;
Button prepareButton;
Button recoverButton;
Button magicButton;
Button quitButtonArena;
Button continueFightButton;

SpriteObject sceneBackground("background", "Assets/FightScene.jpg");

sf::RectangleShape textBoxBackground;
sf::Text characterActionText;
sf::Text turnText;
std::string currentAction = "DOOMSLAYER attacked for 50 damage";
std::string turnString = "Your turn!";

Player player;
Enemy enemy;

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

std::ifstream characterDataArena("PlayerData.txt");
std::vector<int> statsVecArena;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	if (characterDataArena.fail()) {
		std::cout << "\n" << "Failed opening the PlayerData.txt file in Arena.cpp." << std::endl << "\n";
	}
	else {
		std::string line;
		while (getline(characterDataArena, line)) {
			statsVecArena.push_back(std::stoi(line));
		}
		characterDataArena.close();
	}

	//
	player.initializeVariablesPlayer();
	player.handleCharacter(*this);
	enemy.initializeVariablesEnemy();
	enemy.handleCharacter(*this);

	//
	handleBackground();
	adjustSkillScaling(player.m_strength, player.m_heal, player.m_headshot);
	handleTextbox();
	handleButtons();
}

Arena::~Arena() { }

void Arena::handleTextbox() {
	textBoxBackground.setSize(sf::Vector2f(880, 160));
	textBoxBackground.setPosition(sf::Vector2f(520, 20));
	textBoxBackground.setFillColor(sf::Color(0, 0, 0, 150));

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
	attackButton.setColour(sf::Color(255, 0, 0, 120));
	attackButton.setString("Attack", m_font, 40, sf::Color::White);

	prepareButton.setSize(sf::Vector2f(190, 60));
	prepareButton.setPosition(sf::Vector2f(730, 250));
	prepareButton.setColour(sf::Color(125, 125, 125, 120));
	prepareButton.setString("Prepare", m_font, 40, sf::Color::White);

	recoverButton.setSize(sf::Vector2f(190, 60));
	recoverButton.setPosition(sf::Vector2f(950, 250));
	recoverButton.setColour(sf::Color(0, 255, 0, 120));
	recoverButton.setString("Recover", m_font, 40, sf::Color::White);

	magicButton.setSize(sf::Vector2f(210, 60));
	magicButton.setPosition(sf::Vector2f(1190, 250));
	magicButton.setColour(sf::Color(0, 0, 255, 120));
	magicButton.setString("Headshot", m_font, 40, sf::Color::White);

	continueFightButton.setSize(sf::Vector2f(300, 100));
	continueFightButton.setPosition(sf::Vector2f(810, 650));
	continueFightButton.setColour(sf::Color(0, 0, 255, 120));
	continueFightButton.setString("Continue", m_font, 50, sf::Color::Red);

	quitButtonArena.setSize(sf::Vector2f(130, 60));
	quitButtonArena.setPosition(sf::Vector2f(1700, 1000));
	quitButtonArena.setColour(sf::Color::Black);
	quitButtonArena.setString("Quit", m_font, 50, sf::Color::White);

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

void Arena::checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter)
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

void Arena::importCharacter(int p_strength, int p_headshot, int p_intelligence)
{
	player.m_strength = p_strength;
	player.m_headshot = p_headshot;
	player.m_heal = p_intelligence;

	updateSkills();
}

void Arena::updateSkills() {
	player.characterStrengthText.setString(std::to_string(player.m_strength));
	player.characterHealText.setString(std::to_string(player.m_heal));
	player.characterHeadshotText.setString(std::to_string(player.m_heal));
}

void Arena::handleActions(int turn, int action, int damageDealt, int staminaSpent) {
	//int enemyHealthLeft = enemyHealth.getSize().x;
	//int playerStaminaSpent = playerStamina.getSize().x;

	//switch (turn) {
	//case 0:
	//	//Player's turn
	//	switch (action) {
	//	case ATTACK:
	//		if (enemyHealthLeft - damageDealt >= 0) {
	//			enemyHealth.setSize(sf::Vector2f(enemyHealthLeft - damageDealt, 10));
	//			break;
	//		}
	//	case PREPARE:
	//		break;
		/*case HEAL:
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
		}*/
		//case 1:
		//	//Enemy's turn
		//	switch (action) {
		//	case ATTACK:
		//		break;
		//	case PREPARE:
		//		break;
		//	case HEAL:
		//		break;
		//	case HEADSHOT:
		//		break;
		//	}
		//}
}

void Arena::updateActionText(int buttonClicked, std::string characterName, int damageDone, int healthGained) {
	switch (buttonClicked) {
	case ATTACK:
		characterActionText.setString((characterName + " has attacked for: " + std::to_string(damageDone) + " damage!"));
		break;
	case PREPARE:
		characterActionText.setString((characterName + " has prepared for a powerful next attack!"));
		break;
	case HEAL:
		characterActionText.setString((characterName + " has healed for: " + std::to_string(healthGained) + " HP!"));
		break;
	case HEADSHOT:
		characterActionText.setString((characterName + " has dealt " + std::to_string(damageDone) + " headshot damage!"));
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