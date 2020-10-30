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

Text playerStrengthText;
Text playerAgilityText;
Text playerIntelligenceText;

Character player;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	handleBackground();
	handleButtons();
	handlePlayer(windowRef);
}

Arena::~Arena() { }

void Arena::handleText() {
	playerStrengthText.setString(to_string(player.strength));
	playerAgilityText.setString(to_string(player.agility));
	playerIntelligenceText.setString(to_string(player.intelligence));

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

	handleText();
}

void Arena::handleButtons() {
	attackButton.setSize(200, 100);
	attackButton.setPosition(400, 900);
	attackButton.setColour(Color::Transparent);
	attackButton.setString("Attack", m_font, 30, Color::White);

	prepareButton.setSize(200, 100);
	prepareButton.setPosition(700, 900);
	prepareButton.setColour(Color::Transparent);
	prepareButton.setString("Prepare", m_font, 30, Color::White);

	recoverButton.setSize(200, 100);
	recoverButton.setPosition(1000, 900);
	recoverButton.setColour(Color::Transparent);
	recoverButton.setString("Recover", m_font, 30, Color::White);

	magicButton.setSize(200, 100);
	magicButton.setPosition(1300, 900);
	magicButton.setColour(Color::Transparent);
	magicButton.setString("Cast Magic", m_font, 30, Color::White);

	quitButtonArena.setSize(200, 100);
	quitButtonArena.setPosition(1700, 1000);
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

	addRectangleObject(playerBackground);
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

void Arena::importCharacterStats(int p_strength, int p_agility, int p_intelligence)
{
	player.strength = p_strength;
	player.agility = p_agility;
	player.intelligence = p_intelligence;
}
