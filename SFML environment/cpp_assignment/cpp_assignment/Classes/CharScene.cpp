#include <iostream>
#include <fstream>
#include <string>

#include "../Headers/CharScene.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

Button generateButton;
Button cancelButton;
Button fightButton;
SpriteObject background2("background", "charBackground.jpg");

Button strengthButton;
Button agilityButton;
Button intelligenceButton;

Button plusButton;
Button minusButton;

sf::Text intelligenceText;
sf::Text strengthText;
sf::Text agilityText;

Text availablePointsText;

enum Stats {
	STRENGTH = 0,
	AGILITY = 1,
	INTELLIGENCE = 2,
};

Stats playerStats;

int availableSkillPoints = 8;
int minAmountOfSkill = 3;
int maxAmountOfSkill = 10;

Character m_currentPlayer;

CharScene::CharScene() { }

CharScene::CharScene(std::string identifier, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	generateCharacter();

	handleBackground();
	handleText();
	handleButtons();

	//cout << m_currentPlayer.getStrength();
}

CharScene::~CharScene() { }

void CharScene::generateCharacter() {
	//m_currentPlayer.m_strength = 4;
	//m_currentPlayer.m_agility = 4;
	//m_currentPlayer.m_intelligence = 4;

	intelligenceText.setString(to_string(m_currentPlayer.m_intelligence));
	strengthText.setString(to_string(m_currentPlayer.m_strength));
	agilityText.setString(to_string(m_currentPlayer.m_agility));
}

void CharScene::handleText() {
	strengthText.setFont(m_font);
	strengthText.setCharacterSize(100);
	strengthText.setPosition(180, 760);

	agilityText.setFont(m_font);
	agilityText.setCharacterSize(100);
	agilityText.setPosition(580, 760);

	intelligenceText.setFont(m_font);
	intelligenceText.setCharacterSize(100);
	intelligenceText.setPosition(980, 760);

	availablePointsText.setFont(m_font);
	availablePointsText.setCharacterSize(50);
	availablePointsText.setPosition(80, 50);
	availablePointsText.setString(("Available points " + to_string(availableSkillPoints)));

	addTextObject(strengthText);
	addTextObject(agilityText);
	addTextObject(intelligenceText);
	addTextObject(availablePointsText);
}

void CharScene::updateStats() {
	strengthText.setString(to_string(m_currentPlayer.m_strength));
	agilityText.setString(to_string(m_currentPlayer.m_agility));
	intelligenceText.setString(to_string(m_currentPlayer.m_intelligence));
}

void CharScene::handleButtons() {
	minusButton.setPosition(sf::Vector2f(120, 350));
	minusButton.setSprite("MinusButton.png", sf::Vector2f(1.0f, 1.0f));
	minusButton.setSize(sf::Vector2f(100, 100));
	minusButton.setColour(sf::Color::Transparent);

	plusButton.setPosition(sf::Vector2f(270, 350));
	plusButton.setSprite("PlusButton.png", sf::Vector2f(1.0f, 1.0f));
	plusButton.setSize(sf::Vector2f(100, 100));
	plusButton.setColour(sf::Color::Transparent);

	cancelButton.setSize(sf::Vector2f(300, 130));
	cancelButton.setPosition(sf::Vector2f(1250, 440));
	cancelButton.setColour(Color::Transparent);
	cancelButton.setString("Cancel", m_font, 80, Color::White);

	fightButton.setSize(sf::Vector2f(400, 200));
	fightButton.setPosition(sf::Vector2f(1250, 690));
	fightButton.setColour(Color::Transparent);
	fightButton.setString("PLAY", m_font, 100, Color::Red);

	strengthButton.setSprite("strengthIcon.png", sf::Vector2f(0.5f, 0.5f));
	strengthButton.setPosition(sf::Vector2f(100, 500));
	strengthButton.setSize(sf::Vector2f(260, 250));
	strengthButton.setColour(Color::Transparent);

	agilityButton.setSprite("agilityIcon.png", sf::Vector2f(0.5f, 0.5f));
	agilityButton.setPosition(sf::Vector2f(520, 500));
	agilityButton.setSize(sf::Vector2f(260, 250));
	agilityButton.setColour(Color::Transparent);

	intelligenceButton.setSprite("intelligenceIcon.png", sf::Vector2f(0.5f, 0.5f));
	intelligenceButton.setPosition(sf::Vector2f(910, 500));
	intelligenceButton.setSize(sf::Vector2f(260, 250));
	intelligenceButton.setColour(Color::Transparent);

	addGameObject(strengthButton);
	addGameObject(agilityButton);
	addGameObject(intelligenceButton);

	addGameObject(plusButton);
	addGameObject(minusButton);

	addGameObject(fightButton);
	addGameObject(cancelButton);
}

void CharScene::handleBackground() {
	addGameObject(background2);
}

void CharScene::updateSkillPoints(int valueChange) {
	availablePointsText.setString(("Available points " + to_string(availableSkillPoints - valueChange)));
}

void CharScene::writeCharacterToFile() {
	std::ofstream characterFile("PlayerData.txt", std::ostream::out | std::ofstream::trunc);
	if (characterFile.is_open()) {
		characterFile << m_currentPlayer.m_strength << "\n";
		characterFile << m_currentPlayer.m_agility << "\n";
		characterFile << m_currentPlayer.m_intelligence << "\n";
	}
}

void CharScene::importCharacter(int p_strength, int p_agility, int p_intelligence)
{
	m_currentPlayer.m_strength = p_strength;
	m_currentPlayer.m_agility = p_agility;
	m_currentPlayer.m_intelligence = p_intelligence;

	updateStats();
}

void CharScene::checkInput(Event event, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			/*if (generateButton.onClick(mousePos) == true) {
				generateCharacter();
				character.strength = m_currentPlayer.strength;
				character.agility = m_currentPlayer.agility;
				character.intelligence = m_currentPlayer.intelligence;
			}*/

			if (minusButton.onClick(mousePos) == true) {
				switch (playerStats) {
				case STRENGTH:
					if (m_currentPlayer.m_strength > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_strength--;
						strengthText.setString(to_string(m_currentPlayer.m_strength));
					}
					break;
				case AGILITY:
					if (m_currentPlayer.m_agility > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_agility--;
						agilityText.setString(to_string(m_currentPlayer.m_agility));
					}
					break;
				case INTELLIGENCE:
					if (m_currentPlayer.m_intelligence > minAmountOfSkill) {
						availableSkillPoints += 1;
						m_currentPlayer.m_intelligence--;
						intelligenceText.setString(to_string(m_currentPlayer.m_intelligence));
					}
					break;
				}
				availablePointsText.setString(("Available points " + to_string(availableSkillPoints)));
			}

			if ((plusButton.onClick(mousePos) == true) && (availableSkillPoints > 0)) {
				switch (playerStats) {
				case STRENGTH:
					if (m_currentPlayer.m_strength < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_strength++;
						strengthText.setString(to_string(m_currentPlayer.m_strength));
					}
					break;
				case AGILITY:
					if (m_currentPlayer.m_agility < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_agility++;
						agilityText.setString(to_string(m_currentPlayer.m_agility));
					}
					break;
				case INTELLIGENCE:
					if (m_currentPlayer.m_intelligence < maxAmountOfSkill) {
						availableSkillPoints -= 1;
						m_currentPlayer.m_intelligence++;
						intelligenceText.setString(to_string(m_currentPlayer.m_intelligence));
					}
					break;
				}
				availablePointsText.setString(("Available points " + to_string(availableSkillPoints)));
			}

			if (strengthButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(120, 350));
				plusButton.setPosition(sf::Vector2f(270, 350));
				playerStats = STRENGTH;
			}

			if (agilityButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(550, 350));
				plusButton.setPosition(sf::Vector2f(700, 350));
				playerStats = AGILITY;
			}

			if (intelligenceButton.onClick(mousePos) == true) {
				minusButton.setPosition(sf::Vector2f(920, 350));
				plusButton.setPosition(sf::Vector2f(1070, 350));
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