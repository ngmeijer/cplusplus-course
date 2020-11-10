#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Enemy.hpp"
#include "../Headers/Character.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/scene.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

Enemy::Enemy() { }

Enemy::Enemy(std::string identifier) : Character(identifier) { }

Enemy::Enemy(Scene& scene, sf::Font& font) {
	/*m_font = font;*/
}

Enemy::~Enemy() { }

void Enemy::initializeVariablesEnemy() {
	windowBackgroundPos = sf::Vector2f(1410, 10);

	characterHealthPos = sf::Vector2f(1420, 330);
	healthBackgroundPos = sf::Vector2f(1420, 330);

	characterStaminaPos = sf::Vector2f(1420, 380);
	staminaBackgroundPos = sf::Vector2f(1420, 380);

	characterSpritePos = sf::Vector2f(1200, 720);
	m_spriteName = "Assets/Zombie.png";
	m_characterName = "Zombie";

	strengthSpritePos = sf::Vector2f(1440, 120);
	agilitySpritePos = sf::Vector2f(1590, 120);
	intelligenceSpritePos = sf::Vector2f(1740, 120);

	strengthTextPos = sf::Vector2f(1475, 250);
	agilityTextPos = sf::Vector2f(1630, 250);
	intelligenceTextPos = sf::Vector2f(1785, 250);
	characterNamePos = sf::Vector2f(1550, 25);
}