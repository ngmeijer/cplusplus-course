#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(int x, int y, sf::Sprite sprite) {
	_xPosition = x;
	_yPosition = y;
	_sprite = sprite;
	texture.loadFromFile("PixelTexture.png");
	sprite.setTexture(texture);
}

void Player::setSpritePosition(int xPosition, int yPosition) {
	_sprite.setPosition(xPosition, yPosition);
}

double* Player::normalizeMoveSpeed(sf::Vector2<float> axisPosition) {
	double length = sqrt((axisPosition.x * axisPosition.x) + (axisPosition.y * axisPosition.y));
	return &length;
}

void Player::disappear() {
	sf::Color originalColor = _sprite.getColor();
	if (_sprite.getColor() != sf::Color::Transparent)
		_sprite.setColor(sf::Color::Transparent);
}

void Player::show(sf::Color color) {
	_sprite.setColor(color);
}
