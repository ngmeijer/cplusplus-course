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

	this->characterHealth.setSize(sf::Vector2f(healthSize));
	this->characterHealth.setPosition(characterHealthPos);
	this->characterHealth.setFillColor(sf::Color::Red);
	this->healthBackground.setSize(sf::Vector2f(healthSize));
	this->healthBackground.setPosition(healthBackgroundPos);
	this->healthBackground.setFillColor(sf::Color::Black);

	this->characterStamina.setSize(sf::Vector2f(staminaSize));
	this->characterStamina.setPosition(characterStaminaPos);
	this->characterStamina.setFillColor(sf::Color::Blue);
	this->staminaBackground.setSize(sf::Vector2f(staminaSize));
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

void Character::receiveRegDamage(int damageTaken) {
	int healthLeft = this->characterHealth.getSize().x;

	if (healthLeft - damageTaken > 0) {
		this->characterHealth.setSize(sf::Vector2f(healthLeft - damageTaken, 10));
	}
	else {
		this->characterHealth.setSize(sf::Vector2f(0, 10));
	}
}

void Character::handleStamina(int amount) {
	sf::Vector2f size = this->characterStamina.getSize();

	if ((size.x + amount >= 0) && (size.x + amount <= staminaSize.x)) {
		this->characterStamina.setSize(sf::Vector2f(size.x + amount, staminaSize.y));
	}

	if (size.x + amount > staminaSize.x) {
		this->characterStamina.setSize(staminaSize);
	}

}

bool Character::checkStamina(int staminaSpent) {
	sf::Vector2f size = this->characterStamina.getSize();

	bool canSpend = false;
	if (size.x + staminaSpent < 0) {
		canSpend = false;
	}
	else {
		canSpend = true;
	}

	return canSpend;
}

bool Character::canHealSelf(int staminaSpent, int healAmount)
{
	bool canHeal = false;
	int staminaLeft = this->characterStamina.getSize().x;
	int healthLeft = this->characterHealth.getSize().x;

	if ((staminaLeft - staminaSpent > 0) && (healthLeft + healAmount <= healthSize.x)) {
		canHeal = true;
		this->characterHealth.setSize(sf::Vector2f(healthLeft + healAmount, 10));
	}
	else if ((staminaLeft - staminaSpent > 0) && (healthLeft + healAmount > healthSize.x)) {
		canHeal = true;
		this->characterHealth.setSize(sf::Vector2f(healthSize.x, 10));
	}
	else {
		canHeal = false;
	}

	return canHeal;
}

void Character::receiveHeadshot(int damageTaken)
{
	int healthLeft = this->characterHealth.getSize().x;

	if (healthLeft - damageTaken > 0) {
		this->characterHealth.setSize(sf::Vector2f(healthLeft - damageTaken, 10));
	}
	else {
		this->characterHealth.setSize(sf::Vector2f(0, 10));
	}
}

bool Character::isDead() {
	bool hasCharacterDied = false;

	int healthLeft = this->characterHealth.getSize().x;

	if (healthLeft <= 0) {
		hasCharacterDied = true;
	}
	else hasCharacterDied = false;

	return hasCharacterDied;
}

std::string Character::returnCharacterName()
{
	std::string name = this->characterName.getString();

	return name;
}

void Character::findNextDemon()
{
	this->m_spriteName = "Assets/Cacodemon.png";
	this->m_characterName = "Cacodemon";
	this->characterName.setString(m_characterName);
	this->characterName.setPosition(sf::Vector2f(characterNamePos.x - 75, characterNamePos.y));
	this->characterSprite.setSprite(m_spriteName);
	this->characterSprite.setPosition(sf::Vector2f(characterSpritePos.x, characterSpritePos.y - 300));

	this->characterHealth.setSize(healthSize);
	this->characterStamina.setSize(staminaSize);
}

void Character::resetCharacterStats() {
	this->characterHealth.setSize(healthSize);
	this->characterStamina.setSize(staminaSize);
}