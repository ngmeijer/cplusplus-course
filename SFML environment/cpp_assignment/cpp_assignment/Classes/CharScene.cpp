#include <iostream>
#include <fstream>
#include <string>

#include "../Headers/CharScene.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Player.hpp"
#include <fstream>

Button generateButton;
Button cancelButton;
Button fightButton;
SpriteObject background2("background", "Assets/charBackground.jpg");

Button strengthButton;
Button healButton;
Button headshotButton;

Button plusButton;
Button minusButton;

sf::Text headshotText;
sf::Text strengthText;
sf::Text healText;

sf::Text availablePointsText;

std::ifstream characterDataSelect("PlayerData.txt");
std::vector<int> statsVecSelect;

enum Stats {
	STRENGTH = 0,
	AGILITY = 1,
	INTELLIGENCE = 2,
};

Stats playerStats;

int availableSkillPoints = 8;
int minAmountOfSkill = 3;
int maxAmountOfSkill = 10;

Player m_currentPlayer;

CharScene::CharScene() { }

CharScene::CharScene(std::string identifier, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	handleBackground();
	handleText();
	handleButtons();
	importCharacter();
}

CharScene::~CharScene() { }

void CharScene::handleText() {
	strengthText.setFont(m_font);
	strengthText.setCharacterSize(100);
	strengthText.setPosition(210, 900);

	healText.setFont(m_font);
	healText.setCharacterSize(100);
	healText.setPosition(630, 900);

	headshotText.setFont(m_font);
	headshotText.setCharacterSize(100);
	headshotText.setPosition(1010, 900);

	availablePointsText.setFont(m_font);
	availablePointsText.setCharacterSize(90);
	availablePointsText.setPosition(80, 50);
	availablePointsText.setString(("Available points:    " + std::to_string(availableSkillPoints)));

	addTextObject(strengthText);
	addTextObject(healText);
	addTextObject(headshotText);
	addTextObject(availablePointsText);
}

void CharScene::updateStats() {
	strengthText.setString(std::to_string(m_currentPlayer.m_strength));
	healText.setString(std::to_string(m_currentPlayer.m_heal));
	headshotText.setString(std::to_string(m_currentPlayer.m_headshot));

	availablePointsText.setString(("Available points:    " + std::to_string(availableSkillPoints)));
}

void CharScene::handleButtons() {
	minusButton.setPosition(sf::Vector2f(120, 490));
	minusButton.setSprite("Assets/MinusButton.png", sf::Vector2f(1.0f, 1.0f));
	minusButton.setSize(sf::Vector2f(100, 100));
	minusButton.setColour(sf::Color::Transparent);

	plusButton.setPosition(sf::Vector2f(270, 490));
	plusButton.setSprite("Assets/PlusButton.png", sf::Vector2f(1.0f, 1.0f));
	plusButton.setSize(sf::Vector2f(100, 100));
	plusButton.setColour(sf::Color::Transparent);

	cancelButton.setSize(sf::Vector2f(300, 130));
	cancelButton.setPosition(sf::Vector2f(1550, 940));
	cancelButton.setColour(sf::Color::Transparent);
	cancelButton.setString("Cancel", m_font, 80, sf::Color::White);

	fightButton.setSize(sf::Vector2f(500, 230));
	fightButton.setPosition(sf::Vector2f(1350, 20));
	fightButton.setColour(sf::Color::Transparent);
	fightButton.setString("PLAY", m_font, 200, sf::Color::Red);

	strengthButton.setSprite("Assets/StrengthIcon.png", sf::Vector2f(2.0f, 2.0f));
	strengthButton.setPosition(sf::Vector2f(100, 640));
	strengthButton.setSize(sf::Vector2f(260, 250));
	strengthButton.setColour(sf::Color::Transparent);

	healButton.setSprite("Assets/HealIcon.png", sf::Vector2f(2.0f, 2.0f));
	healButton.setPosition(sf::Vector2f(520, 640));
	healButton.setSize(sf::Vector2f(260, 250));
	healButton.setColour(sf::Color::Transparent);

	headshotButton.setSprite("Assets/HeadshotIcon.png", sf::Vector2f(2.0f, 2.0f));
	headshotButton.setPosition(sf::Vector2f(900, 640));
	headshotButton.setSize(sf::Vector2f(260, 250));
	headshotButton.setColour(sf::Color::Transparent);

	addGameObject(strengthButton);
	addGameObject(healButton);
	addGameObject(headshotButton);

	addGameObject(plusButton);
	addGameObject(minusButton);

	addGameObject(fightButton);
	addGameObject(cancelButton);
}

void CharScene::handleBackground() {
	addGameObject(background2);
}

void CharScene::updateSkillPoints(int valueChange) {
	availablePointsText.setString(("Available points:    " + std::to_string(availableSkillPoints - valueChange)));
}

void CharScene::writeCharacterToFile() {
	std::ofstream characterFile("PlayerData.txt");
	if (characterFile.is_open()) {
		characterFile << m_currentPlayer.m_strength << "\n";
		characterFile << m_currentPlayer.m_heal << "\n";
		characterFile << m_currentPlayer.m_headshot << "\n";

		characterFile << availableSkillPoints << "\n";
	}
}

void CharScene::importCharacter()
{
	if (characterDataSelect.is_open())
	{
		std::string line;
		while (getline(characterDataSelect, line)) {
			if (line.empty()) {
				return;
			}
			else {
				std::cout << "value: " << line << std::endl;
				statsVecSelect.push_back(std::stoi(line));
			}
		}

		m_currentPlayer.m_strength = statsVecSelect[0];
		m_currentPlayer.m_heal = statsVecSelect[1];
		m_currentPlayer.m_headshot = statsVecSelect[2];

		availableSkillPoints = statsVecSelect[3];

	}
	else std::cout << "Unable to open file";

	updateStats();
}

void CharScene::checkInput(sf::Event event, sf::Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (minusButton.onClick(mousePos) == true) {
				switch (playerStats) {
				case STRENGTH:
					if (m_currentPlayer.m_strength > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_strength--;
						strengthText.setString(std::to_string(m_currentPlayer.m_strength));
					}
					break;
				case AGILITY:
					if (m_currentPlayer.m_heal > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_heal--;
						healText.setString(std::to_string(m_currentPlayer.m_heal));
					}
					break;
				case INTELLIGENCE:
					if (m_currentPlayer.m_headshot > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_headshot--;
						headshotText.setString(std::to_string(m_currentPlayer.m_headshot));
					}
					break;
				}
				availablePointsText.setString(("Available points:    " + std::to_string(availableSkillPoints)));
			}

			if ((plusButton.onClick(mousePos) == true) && (availableSkillPoints > 0)) {
				switch (playerStats) {
				case STRENGTH:
					if (m_currentPlayer.m_strength < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_strength++;
						strengthText.setString(std::to_string(m_currentPlayer.m_strength));
					}
					break;
				case AGILITY:
					if (m_currentPlayer.m_heal < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_heal++;
						healText.setString(std::to_string(m_currentPlayer.m_heal));
					}
					break;
				case INTELLIGENCE:
					if (m_currentPlayer.m_headshot < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_headshot++;
						headshotText.setString(std::to_string(m_currentPlayer.m_headshot));
					}
					break;
				}
				availablePointsText.setString(("Available points:    " + std::to_string(availableSkillPoints)));
			}

			if (strengthButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(120, 490));
				plusButton.setPosition(sf::Vector2f(270, 490));
				playerStats = STRENGTH;
			}

			if (healButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(550, 490));
				plusButton.setPosition(sf::Vector2f(700, 490));
				playerStats = AGILITY;
			}

			if (headshotButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(920, 490));
				plusButton.setPosition(sf::Vector2f(1070, 490));
				playerStats = INTELLIGENCE;
			}

			if (cancelButton.onClick(mousePos) == true) {
				counter--;
				handler.stackScene("menu");
			}

			if (fightButton.onClick(mousePos) == true) {
				writeCharacterToFile();
				handler.stackScene("arena");
				counter++;
			}
		}
	}
}