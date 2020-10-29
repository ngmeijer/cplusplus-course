#include <iostream>

#include "../Headers/CharScene.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

Button generateButton;
Button cancelButton;
Button fightButton;
SpriteObject strengthIcon("strengthIcon", "strengthIcon.png");
SpriteObject agilityIcon("agilityIcon", "agilityIcon.png");
SpriteObject witsIcon("witsIcon", "witsIcon.png");
SpriteObject background2("background", "charBackground.jpg");

Text witsText;
Text strengthText;
Text agilityText;

Character character;

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
	character.strength = character.GenerateValues(75, 100);
	character.agility = character.GenerateValues(75, 100);
	character.intelligence = character.GenerateValues(75, 100);

	witsText.setString(to_string(character.intelligence));
	strengthText.setString(to_string(character.strength));
	agilityText.setString(to_string(character.agility));
}

void CharScene::handleText(RenderWindow& window) {
	strengthText.setFont(m_font);
	strengthText.setCharacterSize(100);
	strengthText.setPosition(180, 760);
	strengthText.setString(to_string(character.strength));

	agilityText.setFont(m_font);
	agilityText.setCharacterSize(100);
	agilityText.setPosition(580, 760);
	agilityText.setString(to_string(character.agility));

	witsText.setFont(m_font);
	witsText.setCharacterSize(100);
	witsText.setPosition(980, 760);
	witsText.setString(to_string(character.intelligence));

	addTextObject(strengthText);
	addTextObject(agilityText);
	addTextObject(witsText);
}

void CharScene::handleButtons() {
	generateButton.setSize(400, 200);
	generateButton.setPosition(1250, 190);
	generateButton.setColour(Color::Transparent);
	generateButton.setString("Generate", m_font, 80, Color::White);

	cancelButton.setSize(300, 130);
	cancelButton.setPosition(1250, 440);
	cancelButton.setColour(Color::Transparent);
	cancelButton.setString("Cancel", m_font, 80, Color::White);

	fightButton.setSize(400, 200);
	fightButton.setPosition(1250, 690);
	fightButton.setColour(Color::Transparent);
	fightButton.setString("PLAY", m_font, 100, Color::Red);

	strengthIcon.setPosition(sf::Vector2f(100, 500));
	strengthIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	agilityIcon.setPosition(sf::Vector2f(500, 500));
	agilityIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	witsIcon.setPosition(sf::Vector2f(900, 500));
	witsIcon.setScale(sf::Vector2f(0.5f, 0.5f));

	addGameObject(fightButton);
	addGameObject(generateButton);
	addGameObject(cancelButton);

	addGameObject(witsIcon);
	addGameObject(agilityIcon);
	addGameObject(strengthIcon);
}

void CharScene::handleBackground() {
	addGameObject(background2);
}

void CharScene::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (generateButton.onClick(mousePos) == true) {
				generateCharacter();
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