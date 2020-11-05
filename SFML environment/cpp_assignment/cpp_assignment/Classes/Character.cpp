#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Character.hpp"
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"

Character::Character() { }

Character::Character(std::string identifier) : GameObject(identifier) {

	handleCharacter(m_scene);

	int testX = windowBackgroundPos.x;
	int testY = windowBackgroundPos.y;
	std::cout << "x: " << testX << ", y: " << testY << std::endl;
}

Character::~Character() { }

void Character::handleCharacterText(Scene& scene) {
	this->characterStrengthText.setString(std::to_string(m_strength));
	this->characterAgilityText.setString(std::to_string(m_intelligence));
	this->characterIntelligenceText.setString(std::to_string(m_intelligence));

	if (!m_font.loadFromFile("Assets/font.ttf")) {
		std::cout << "Couldn't load font." << std::endl;
	}

	characterName.setFont(m_font);
	characterStrengthText.setFont(m_font);
	characterAgilityText.setFont(m_font);
	characterIntelligenceText.setFont(m_font);

	characterName.setPosition(characterNamePos);
	characterStrengthText.setPosition(strengthTextPos);
	characterAgilityText.setPosition(agilityTextPos);
	characterIntelligenceText.setPosition(intelligenceTextPos);

	characterName.setCharacterSize(65);
	characterStrengthText.setCharacterSize(50);
	characterAgilityText.setCharacterSize(50);
	characterIntelligenceText.setCharacterSize(50);

	scene.addTextObject(characterName);
	scene.addTextObject(characterStrengthText);
	scene.addTextObject(characterAgilityText);
	scene.addTextObject(characterIntelligenceText);
}

void Character::handleCharacter(Scene& scene) {
	handleCharacterSprites(scene);
	handleCharacterText(scene);
}

void Character::handleCharacterSprites(Scene& scene) {
	scene.addRectangleObject(this->windowBackground);
	scene.addSpriteObject(this->characterSprite);
	scene.addSpriteObject(this->strengthSprite);
	scene.addSpriteObject(this->agilitySprite);
	scene.addSpriteObject(this->intelligenceSprite);

	scene.addRectangleObject(this->healthBackground);
	scene.addRectangleObject(this->characterHealth);
	scene.addRectangleObject(this->staminaBackground);
	scene.addRectangleObject(this->characterStamina);

	this->windowBackground.setSize(sf::Vector2f(500, 400));
	this->windowBackground.setPosition(windowBackgroundPos);
	this->windowBackground.setFillColor(sf::Color(120, 120, 120, 150));

	this->characterName.setString(m_characterName);

	this->characterSprite.setSprite(m_spriteName);
	this->characterSprite.setPosition(characterSpritePos);
	this->characterSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	this->characterHealth.setSize(sf::Vector2f(480, 10));
	this->characterHealth.setPosition(characterHealthPos);
	this->characterHealth.setFillColor(sf::Color::Red);
	this->healthBackground.setSize(sf::Vector2f(480, 10));
	this->healthBackground.setPosition(healthBackgroundPos);
	this->healthBackground.setFillColor(sf::Color::Black);

	this->characterStamina.setSize(sf::Vector2f(480, 10));
	this->characterStamina.setPosition(characterStaminaPos);
	this->characterStamina.setFillColor(sf::Color::Blue);
	this->staminaBackground.setSize(sf::Vector2f(480, 10));
	this->staminaBackground.setPosition(staminaBackgroundPos);
	this->staminaBackground.setFillColor(sf::Color::Black);

	this->strengthSprite.setSprite("Assets/StrengthIcon.png");
	this->strengthSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->agilitySprite.setSprite("Assets/AgilityIcon.png");
	this->agilitySprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->intelligenceSprite.setSprite("Assets/IntelligenceIcon.png");
	this->intelligenceSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->strengthSprite.setPosition(strengthSpritePos);
	this->agilitySprite.setPosition(agilitySpritePos);
	this->intelligenceSprite.setPosition(intelligenceSpritePos);
}

void Character::render(sf::RenderWindow& window) { }

void Character::update() { }