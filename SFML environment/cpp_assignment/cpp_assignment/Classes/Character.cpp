#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Character.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/scene.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

sf::Text characterStrengthText;
sf::Text characterAgilityText;
sf::Text characterIntelligenceText;

sf::Font m_font;
Scene* m_scene;

sf::Vector2f m_characterPosition;
std::string m_spriteName;

Character::Character() { }

Character::Character(std::string identifier, Scene& scene, sf::Font& font) : GameObject(identifier) {
	m_font = font;
}

Character::~Character() { }

int Character::GenerateValues(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(min, max);

	int value = distr(gen);

	return value;
}

void Character::handleCharacterText(Scene& scene, sf::Text& strength, sf::Text& agility, sf::Text& intelligence) {
	strength.setString(std::to_string(m_strength));
	agility.setString(std::to_string(m_intelligence));
	intelligence.setString(std::to_string(m_intelligence));

	if (!m_font.loadFromFile("font.ttf")) {
		std::cout << "Couldn't load font." << std::endl;
	}

	strength.setFont(m_font);
	agility.setFont(m_font);
	intelligence.setFont(m_font);

	strength.setPosition(70, 200);
	agility.setPosition(240, 200);
	intelligence.setPosition(410, 200);

	strength.setCharacterSize(50);
	agility.setCharacterSize(50);
	intelligence.setCharacterSize(50);

	scene.addTextObject(strength);
	scene.addTextObject(agility);
	scene.addTextObject(intelligence);
}

void Character::handleCharacter(Scene& scene, sf::Vector2f characterSpritePosition, std::string spriteName) {
	m_spriteName = spriteName;
	m_characterPosition = characterSpritePosition;
	handleCharacterSprites(scene);
	handleCharacterText(scene, characterStrengthText, characterAgilityText, characterIntelligenceText);
}

void Character::handleCharacterSprites(Scene& scene) {
	scene.addRectangleObject(this->windowBackground);
	scene.addSpriteObject(this->characterSprite);
	scene.addSpriteObject(this->characterStrengthSprite);
	scene.addSpriteObject(this->characterAgilitySprite);
	scene.addSpriteObject(this->characterIntelligenceSprite);
	scene.addRectangleObject(this->characterHealthBackground);
	scene.addRectangleObject(this->characterHealth);
	scene.addRectangleObject(this->characterStamina);

	this->windowBackground.setSize(sf::Vector2f(500, 400));
	this->windowBackground.setPosition(sf::Vector2f(m_characterPosition.x - 490, m_characterPosition.y - 320));
	this->windowBackground.setFillColor(sf::Color(120, 120, 120, 150));

	this->characterSprite.setSprite(m_spriteName);
	this->characterSprite.setPosition(sf::Vector2f(m_characterPosition.x + 100, m_characterPosition.y + 200));
	this->characterSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	this->characterHealth.setSize(sf::Vector2f(480, 10));
	this->characterHealth.setPosition(sf::Vector2f(m_characterPosition.x + 20, m_characterPosition.y + 130));
	this->characterHealth.setFillColor(sf::Color::Red);

	this->characterHealthBackground.setSize(sf::Vector2f(480, 10));
	this->characterHealthBackground.setPosition(sf::Vector2f(20, 330));
	this->characterHealthBackground.setFillColor(sf::Color::Black);

	this->characterStamina.setSize(sf::Vector2f(480, 10));
	this->characterStamina.setPosition(sf::Vector2f(20, 360));
	this->characterStamina.setFillColor(sf::Color::Blue);

	this->characterStrengthSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	this->characterAgilitySprite.setScale(sf::Vector2f(1.0f, 1.0f));
	this->characterIntelligenceSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	this->characterStrengthSprite.setPosition(sf::Vector2f(m_characterPosition.x + 100, m_characterPosition.y + 200));
	this->characterAgilitySprite.setPosition(sf::Vector2f(190, 75));
	this->characterIntelligenceSprite.setPosition(sf::Vector2f(360, 75));
}

void Character::render(sf::RenderWindow& window) { }

void Character::update() { }