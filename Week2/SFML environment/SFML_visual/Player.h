#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	int _xPosition;
	int _yPosition;
	sf::Sprite _sprite;
	sf::Texture texture;

public:
	Player(int x, int y, sf::Sprite sprite);

	void setSpritePosition(int xPosition, int yPosition);

	double* normalizeMoveSpeed(sf::Vector2<float> axisPosition);

	void disappear();

	void show(sf::Color color);
};