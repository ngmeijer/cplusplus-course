#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Character.hpp"
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"

Character::Character() { }

Character::Character(std::string identifier) : GameObject(identifier) {

	handleCharacter(m_scene);
}

Character::~Character() { }

void Character::handleCharacterText(Scene& scene) {
	this->characterStrengthText.setString(std::to_string(m_strength));
	this->characterHealText.setString(std::to_string(m_heal));
	this->characterHeadshotText.setString(std::to_string(m_headshot));

	if (!m_font.loadFromFile("Assets/font.ttf")) {
		std::cout << "Couldn't load font." << std::endl;
	}

	characterName.setFont(m_font);
	characterStrengthText.setFont(m_font);
	characterHealText.setFont(m_font);
	characterHeadshotText.setFont(m_font);

	characterName.setPosition(characterNamePos);
	characterStrengthText.setPosition(strengthTextPos);
	characterHealText.setPosition(agilityTextPos);
	characterHeadshotText.setPosition(intelligenceTextPos);

	characterName.setCharacterSize(65);
	characterStrengthText.setCharacterSize(50);
	characterHealText.setCharacterSize(50);
	characterHeadshotText.setCharacterSize(50);

	scene.addTextObject(characterName);
	scene.addTextObject(characterStrengthText);
	scene.addTextObject(characterHealText);
	scene.addTextObject(characterHeadshotText);
}

void Character::handleCharacter(Scene& scene) {
	handleCharacterSprites(scene);
	handleCharacterText(scene);
}

void Character::handleCharacterSprites(Scene& scene) {
	scene.addRectangleObject(this->windowBackground);
	scene.addSpriteObject(this->characterSprite);
	scene.addSpriteObject(this->strengthSprite);
	scene.addSpriteObject(this->healSprite);
	scene.addSpriteObject(this->headshotSprite);

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

	this->healSprite.setSprite("Assets/HealIcon.png");
	this->healSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->headshotSprite.setSprite("Assets/HeadshotIcon.png");
	this->headshotSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->strengthSprite.setPosition(strengthSpritePos);
	this->healSprite.setPosition(agilitySpritePos);
	this->headshotSprite.setPosition(intelligenceSpritePos);
}

void Character::render(sf::RenderWindow& window) { }

void Character::update() { }

void Character::importStats(int p_strength, int p_headshot, int p_intelligence)
{
	this->m_strength = p_strength;
	this->m_headshot = p_headshot;
	this->m_heal = p_intelligence;
}
