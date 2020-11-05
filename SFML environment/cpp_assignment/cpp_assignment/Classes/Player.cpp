#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Player.hpp"
#include "../Headers/Character.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/scene.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

Player::Player() { }

Player::Player(std::string identifier) : Character(identifier) { }

Player::Player(Scene& scene, sf::Font& font) {
	m_font = font;
}

Player::~Player() { }

void Player::initializeVariablesPlayer() {
	windowBackgroundPos = sf::Vector2f(10, 10);

	characterHealthPos = sf::Vector2f(20, 330);
	healthBackgroundPos = sf::Vector2f(20, 330);

	characterStaminaPos = sf::Vector2f(20, 380);
	staminaBackgroundPos = sf::Vector2f(20, 380);

	characterSpritePos = sf::Vector2f(475, 515);
	m_spriteName = "Assets/DoomSlayer.png";
	m_characterName = "DOOMSLAYER";

	strengthSpritePos = sf::Vector2f(40, 120);
	agilitySpritePos = sf::Vector2f(190, 120);
	intelligenceSpritePos = sf::Vector2f(340, 120);

	strengthTextPos = sf::Vector2f(75, 250);
	agilityTextPos = sf::Vector2f(230, 250);
	intelligenceTextPos = sf::Vector2f(380, 250);
	characterNamePos = sf::Vector2f(50, 25);
}