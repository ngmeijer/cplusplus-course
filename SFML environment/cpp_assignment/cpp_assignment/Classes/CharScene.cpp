#include <iostream>

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

Text intelligenceText;
Text strengthText;
Text agilityText;


enum Stats {
	STRENGTH = 0,
	AGILITY = 1,
	INTELLIGENCE = 2,
};

Stats playerStats;

Character m_currentPlayer;

CharScene::CharScene() { }

CharScene::CharScene(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	generateCharacter();

	handleBackground();
	handleText(windowRef);
	handleButtons();
}

CharScene::~CharScene() { }

void CharScene::generateCharacter() {
	m_currentPlayer.strength = m_currentPlayer.GenerateValues(75, 100);
	m_currentPlayer.agility = m_currentPlayer.GenerateValues(75, 100);
	m_currentPlayer.intelligence = m_currentPlayer.GenerateValues(75, 100);

	intelligenceText.setString(to_string(m_currentPlayer.intelligence));
	strengthText.setString(to_string(m_currentPlayer.strength));
	agilityText.setString(to_string(m_currentPlayer.agility));
}

void CharScene::handleText(RenderWindow& window) {
	strengthText.setFont(m_font);
	strengthText.setCharacterSize(100);
	strengthText.setPosition(180, 760);
	strengthText.setString(to_string(m_currentPlayer.strength));

	agilityText.setFont(m_font);
	agilityText.setCharacterSize(100);
	agilityText.setPosition(580, 760);
	agilityText.setString(to_string(m_currentPlayer.agility));

	intelligenceText.setFont(m_font);
	intelligenceText.setCharacterSize(100);
	intelligenceText.setPosition(980, 760);
	intelligenceText.setString(to_string(m_currentPlayer.intelligence));

	addTextObject(strengthText);
	addTextObject(agilityText);
	addTextObject(intelligenceText);
}

void CharScene::handleButtons() {
	/*generateButton.setSize(sf::Vector2f(400, 200));
	generateButton.setPosition(sf::Vector2f(1250, 190));
	generateButton.setColour(Color::Transparent);
	generateButton.setString("Generate", m_font, 80, Color::White);*/

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

	//agilityIcon.setPosition(sf::Vector2f(500, 500));
	//agilityIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	//witsIcon.setPosition(sf::Vector2f(900, 500));
	//witsIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	addGameObject(strengthButton);
	addGameObject(agilityButton);
	addGameObject(intelligenceButton);

	addGameObject(plusButton);
	addGameObject(minusButton);

	addGameObject(fightButton);
	//addGameObject(generateButton);
	addGameObject(cancelButton);

	//addGameObject(witsIcon);
	//addGameObject(agilityIcon);
	//addGameObject(strengthIcon);
}

void CharScene::handleBackground() {
	addGameObject(background2);
}

void CharScene::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter, Character& character)
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
					m_currentPlayer.strength--;
					cout << character.strength << endl;
					strengthText.setString(to_string(m_currentPlayer.strength));
					break;
				case AGILITY:
					m_currentPlayer.agility--;
					agilityText.setString(to_string(m_currentPlayer.agility));
					break;
				case INTELLIGENCE:
					m_currentPlayer.intelligence--;
					intelligenceText.setString(to_string(m_currentPlayer.intelligence));
					break;
				}
			}

			if (plusButton.onClick(mousePos) == true) {
				switch (playerStats) {
				case STRENGTH:
					m_currentPlayer.strength++;
					strengthText.setString(to_string(m_currentPlayer.strength));
					break;
				case AGILITY:
					m_currentPlayer.agility++;
					agilityText.setString(to_string(m_currentPlayer.agility));
					break;
				case INTELLIGENCE:
					m_currentPlayer.intelligence++;
					cout << character.intelligence << endl;
					intelligenceText.setString(to_string(m_currentPlayer.intelligence));
					break;
				}
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
				handler.stackScene("arena");
				counter++;
			}
		}
	}
}