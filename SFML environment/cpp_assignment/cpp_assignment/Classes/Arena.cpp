#include <iostream>
#include <fstream>
#include <random>

#include "../Headers/Arena.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Player.hpp"
#include "../Headers/Enemy.hpp"

Button attackButtonArena;
Button prepareButtonArena;
Button recoverButtonArena;
Button headshotButtonArena;
Button quitButtonArena;
Button continueFightButtonArena;

SpriteObject sceneBackground("background", "Assets/FightScene.jpg");

sf::RectangleShape textBoxBackground;
sf::Text characterActionText;
sf::Text turnText;
std::string currentAction = "DOOMSLAYER attacked for 50 damage";
std::string turnString = "Your turn!";

Player player;
Enemy enemy;

int currentTurn;
int enemiesDefeated;
int turnsUsed;

enum CHARACTERS {
	PLAYER,
	ENEMY,
};

enum ACTION_BUTTONS {
	ATTACK,
	PREPARE,
	HEAL,
	HEADSHOT,
	DO_NOTHING,
};

ACTION_BUTTONS selectionAction;
Arena::ACTION_VALUES actionValuesPlayer;
Arena::ACTION_VALUES actionValuesEnemy;
CHARACTERS characters;

std::ifstream characterDataArena("Save data/PlayerData.cmgt");
std::vector<int> statsVecArena;

std::string enemyName;
std::string playerName;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	//
	player.initializeVariablesPlayer();
	enemy.initializeVariablesEnemy();
	enemy.generateCharacter();
	adjustSkillScaling(actionValuesEnemy, enemy, enemy.m_strength, enemy.m_heal, enemy.m_headshot);
	enemy.handleCharacter(*this);
	adjustSkillScaling(actionValuesPlayer, player, player.m_strength, player.m_heal, player.m_headshot);
	player.handleCharacter(*this);

	//

	handleBackground();
	handleTextbox();
	handleButtons();
	enemyName = enemy.returnCharacterName();
	playerName = player.returnCharacterName();

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
	turnText.setPosition(sf::Vector2f(525, 130));
	turnText.setCharacterSize(40);

	addTextObject(characterActionText);
	addTextObject(turnText);
}

void Arena::handleButtons() {
	attackButtonArena.setSize(sf::Vector2f(190, 60));
	attackButtonArena.setPosition(sf::Vector2f(520, 200));
	attackButtonArena.setColour(sf::Color(0, 0, 255, 150));
	attackButtonArena.setString("Attack", m_font, 40, sf::Color::White);

	prepareButtonArena.setSize(sf::Vector2f(210, 60));
	prepareButtonArena.setPosition(sf::Vector2f(730, 200));
	prepareButtonArena.setColour(sf::Color(0, 0, 255, 150));
	prepareButtonArena.setString("Prepare", m_font, 40, sf::Color::White);

	recoverButtonArena.setSize(sf::Vector2f(210, 60));
	recoverButtonArena.setPosition(sf::Vector2f(950, 200));
	recoverButtonArena.setColour(sf::Color(0, 0, 255, 150));
	recoverButtonArena.setString("Recover", m_font, 40, sf::Color::White);

	headshotButtonArena.setSize(sf::Vector2f(230, 60));
	headshotButtonArena.setPosition(sf::Vector2f(1170, 200));
	headshotButtonArena.setColour(sf::Color(0, 0, 255, 150));
	headshotButtonArena.setString("Headshot", m_font, 40, sf::Color::White);

	continueFightButtonArena.setSize(sf::Vector2f(315, 90));
	continueFightButtonArena.setPosition(sf::Vector2f(810, 300));
	continueFightButtonArena.setColour(sf::Color(0, 0, 255, 150));
	continueFightButtonArena.setString("Continue", m_font, 60, sf::Color::White);

	quitButtonArena.setSize(sf::Vector2f(130, 60));
	quitButtonArena.setPosition(sf::Vector2f(1700, 1000));
	quitButtonArena.setColour(sf::Color::Black);
	quitButtonArena.setString("Quit", m_font, 50, sf::Color::White);

	addGameObject(attackButtonArena);
	addGameObject(prepareButtonArena);
	addGameObject(recoverButtonArena);
	addGameObject(headshotButtonArena);
	addGameObject(continueFightButtonArena);
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

			if (currentTurn == PLAYER) {
				if (attackButtonArena.onClick(mousePos) == true) {
					updateActionText(currentTurn, ATTACK, 75, 0, enemyName);
					handleActions(0, ATTACK, 75, 75, 0);
				}

				if (prepareButtonArena.onClick(mousePos) == true) {
					std::cout << enemyName << std::endl;
					updateActionText(currentTurn, PREPARE, 0, 0, enemyName);
					handleActions(0, PREPARE, 0, 150, 0);
				}

				if (recoverButtonArena.onClick(mousePos) == true) {
					updateActionText(currentTurn, HEAL, 0, 100, enemyName);
					handleActions(0, HEAL, 0, 50, 100);
				}

				if (headshotButtonArena.onClick(mousePos) == true) {
					updateActionText(currentTurn, HEADSHOT, 150, 0, enemyName);
					handleActions(0, HEADSHOT, 150, 150, 0);
				}

				if (enemy.isDead()) {
					enemiesDefeated++;
					showBattleWonScreen(handler, counter);
					enemy.findNextDemon();
					player.resetCharacterStats();
					enemyName = enemy.returnCharacterName();
				}
			}

			if (currentTurn == ENEMY) {
				if (continueFightButtonArena.onClick(mousePos) == true) {
					int action = generateRandomAction();
					updateActionText(currentTurn, action, 100, 50, enemyName);
					handleActions(1, action, 50, 50, 50);
					if (player.isDead()) {
						handler.stackScene("gameover");
						counter++;
					}
				}
			}
		}
	}
}

void Arena::showBattleWonScreen(SceneHandler& handler, int& counter) {
	characterActionText.setString(enemyName + " has been defeated!");

	if (enemiesDefeated >= 2) {
		handler.stackScene("gameover");
		counter++;
	}
}

int Arena::generateRandomAction()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(ACTION_BUTTONS::ATTACK, ACTION_BUTTONS::DO_NOTHING);

	int value = distr(gen);

	return value;
}

void Arena::importCharacter()
{
	if (characterDataArena.is_open())
	{
		//Variables don't get replaced so old values are used in vector, therefore not updating character skills?
		std::string line;
		while (getline(characterDataArena, line)) {
			statsVecArena.push_back(std::stoi(line));
		}

		player.m_strength = statsVecArena[0];
		player.m_heal = statsVecArena[1];
		player.m_headshot = statsVecArena[2];

		std::cout << "reimporting character in Arena.cpp" << std::endl;

		characterDataArena.close();
	}
	else std::cout << "Unable to open PlayerData.cmgt in Arena.cpp" << std::endl;

	for (int i = 0; i < statsVecArena.size(); i++) {
		std::cout << "vector element: " << statsVecArena[i] << std::endl;
	}

	updateSkills();
}

void Arena::updateSkills() {
	player.characterStrengthText.setString(std::to_string(player.m_strength));
	player.characterHealText.setString(std::to_string(player.m_heal));
	player.characterHeadshotText.setString(std::to_string(player.m_headshot));
}

void Arena::handleActions(int turn, int action, int damageDealt, int staminaAmount, int healAmount) {
	switch (turn) {
	case PLAYER:
		turnsUsed++;
		switch (action) {
		case ATTACK:
			if (player.checkStamina(-staminaAmount)) {
				enemy.receiveRegDamage(actionValuesPlayer.attackDamage);
				player.handleStamina(-staminaAmount);
				turn = ENEMY;
				currentTurn = ENEMY;
			}
			else {
				characterActionText.setString("Not enough Stamina! PREPARE to gain it!");
			}
			break;

		case PREPARE:
			player.handleStamina(staminaAmount);
			turn = ENEMY;
			currentTurn = ENEMY;
			break;

		case HEAL:
			if (player.checkStamina(-staminaAmount)) {
				player.canHealSelf(staminaAmount, actionValuesPlayer.healAmount);
				player.handleStamina(-staminaAmount);
				turn = ENEMY;
				currentTurn = ENEMY;
			}
			else {
				characterActionText.setString("Not enough Stamina! PREPARE to gain it!");
			}
			break;

		case HEADSHOT:
			if (player.checkStamina(-staminaAmount)) {
				enemy.receiveHeadshot(actionValuesPlayer.headshotDamage);
				player.handleStamina(-staminaAmount);
				turn = ENEMY;
				currentTurn = ENEMY;
			}
			else {
				characterActionText.setString("Not enough Stamina! PREPARE to gain it!");
			}
			break;
		}
		break;
	case ENEMY:
		switch (action) {
		case ATTACK:
			if (enemy.checkStamina(staminaAmount)) {
				player.receiveRegDamage(actionValuesEnemy.attackDamage);
				enemy.handleStamina(-staminaAmount);
			}
			else {
				enemy.handleStamina(staminaAmount);
			}
			turn = PLAYER;
			currentTurn = PLAYER;
			break;

		case PREPARE:
			enemy.handleStamina(staminaAmount);
			turn = PLAYER;
			currentTurn = PLAYER;
			break;

		case HEAL:
			if (enemy.checkStamina(staminaAmount)) {
				enemy.canHealSelf(staminaAmount, actionValuesEnemy.healAmount);
			}
			else {
				enemy.handleStamina(staminaAmount);
			}
			turn = PLAYER;
			currentTurn = PLAYER;
			break;

		case HEADSHOT:
			if (enemy.checkStamina(staminaAmount)) {
				player.receiveHeadshot(actionValuesEnemy.headshotDamage);
			}
			else {
				enemy.handleStamina(staminaAmount);
			}
			turn = PLAYER;
			currentTurn = PLAYER;
			break;

		case DO_NOTHING:
			turn = PLAYER;
			currentTurn = PLAYER;
			break;
		}
		break;
	}
}

void Arena::updateActionText(int turn, int buttonClicked, int damageDone, int healthGained, std::string enemyName) {
	std::cout << "enemy's name: " << enemyName << std::endl;
	switch (turn) {
	case PLAYER:
		turnText.setString(enemyName + "'s turn!");
		switch (buttonClicked) {
		case ATTACK:
			characterActionText.setString(("DOOMSLAYER has attacked for: " + std::to_string(damageDone) + " damage!"));
			break;
		case PREPARE:
			characterActionText.setString(("DOOMSLAYER has regained stamina!"));
			break;
		case HEAL:
			characterActionText.setString(("DOOMSLAYER has healed for: " + std::to_string(healthGained) + " HP!"));
			break;
		case HEADSHOT:
			characterActionText.setString(("DOOMSLAYER has dealt " + std::to_string(damageDone) + " headshot damage!"));
			break;
		}
		break;
	case ENEMY:
		turnText.setString("DOOMSLAYERS turn!");
		switch (buttonClicked) {
		case ATTACK:
			characterActionText.setString((enemyName + " has attacked for: " + std::to_string(damageDone) + " damage!"));
			break;
		case PREPARE:
			characterActionText.setString((enemyName + " has regained stamina!"));
			break;
		case HEAL:
			characterActionText.setString((enemyName + " has healed for: " + std::to_string(healthGained) + " HP!"));
			break;
		case HEADSHOT:
			characterActionText.setString((enemyName + " has dealt " + std::to_string(damageDone) + " headshot damage!"));
			break;
		case DO_NOTHING:
			characterActionText.setString(enemyName + " has... done nothing?! \nPerhaps he wants peace.....");
		}
		break;
	}
}

void Arena::adjustSkillScaling(ACTION_VALUES values, Character& character, int strength, int heal, int headshot) {
	switch (strength) {
	case 3:
		values.attackDamage = character.strengthValues.strength3;
		break;
	case 4:
		values.attackDamage = character.strengthValues.strength4;
		break;
	case 5:
		values.attackDamage = character.strengthValues.strength5;
		break;
	case 6:
		values.attackDamage = character.strengthValues.strength6;
		break;
	case 7:
		values.attackDamage = character.strengthValues.strength7;
		break;
	case 8:
		values.attackDamage = character.strengthValues.strength8;
		break;
	case 9:
		values.attackDamage = character.strengthValues.strength9;
		break;
	case 10:
		values.attackDamage = character.strengthValues.strength10;
		break;
	}

	switch (heal) {
	case 3:
		values.healAmount = character.healValues.heal3;
		break;
	case 4:
		values.healAmount = character.healValues.heal4;
		break;
	case 5:
		values.healAmount = character.healValues.heal5;
		break;
	case 6:
		values.healAmount = character.healValues.heal6;
		break;
	case 7:
		values.healAmount = character.healValues.heal7;
		break;
	case 8:
		values.healAmount = character.healValues.heal8;
		break;
	case 9:
		values.healAmount = character.healValues.heal9;
		break;
	case 10:
		values.healAmount = character.healValues.heal10;
		break;
	}

	switch (headshot) {
	case 3:
		values.headshotDamage = character.headshotValues.headshot3;
		break;
	case 4:
		values.headshotDamage = character.headshotValues.headshot4;
		break;
	case 5:
		values.headshotDamage = character.headshotValues.headshot5;
		break;
	case 6:
		values.headshotDamage = character.headshotValues.headshot6;
		break;
	case 7:
		values.headshotDamage = character.headshotValues.headshot7;
		break;
	case 8:
		values.headshotDamage = character.headshotValues.headshot8;
		break;
	case 9:
		values.headshotDamage = character.headshotValues.headshot9;
		break;
	case 10:
		values.headshotDamage = character.headshotValues.headshot10;
		break;
	}
}