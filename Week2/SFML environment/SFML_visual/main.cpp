#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <time.h>
#include "Player.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

float moveVelocity = 1000000.0f;

bool movingLeft = false;
bool movingRight = false;
bool movingUp = false;
bool movingDown = false;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML_visual");
const int MAX_SPRITES = 7;

int randomXosition;

using namespace std;

sf::Texture texture;
sf::Sprite sprite;
int xPositionsArray[MAX_SPRITES];
int yPositionsArray[MAX_SPRITES];
float xPosition;
float yPosition;
vector<Player> spriteArray;
int CURRENT_SPRITE;


void movePlayer() {
	sf::Clock clock;
	clock.restart();
	float deltaTime = clock.restart().asSeconds();

	for (int index = 0; index < MAX_SPRITES; index++) {
		sf::Vector2f velocity(0.0f, 0.0f);
		sf::Vector2f acceleration(moveVelocity, moveVelocity);

		int* xPositionsArrayPtr = &xPositionsArray[index];
		int* yPositionsArrayPtr = &yPositionsArray[index];

		window.draw(spriteArray[index]._sprite);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr -= (velocity.x = acceleration.x * deltaTime), *yPositionsArrayPtr);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr += (velocity.x = acceleration.x * deltaTime), *yPositionsArrayPtr);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr, *yPositionsArrayPtr += (velocity.y = acceleration.y * deltaTime));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr, *yPositionsArrayPtr -= (velocity.y = acceleration.y * deltaTime));
		}

	}
}

void changeColor() {
	for (int index = 0; index < MAX_SPRITES; index++) {
		sf::Color originalColor = spriteArray[0]._sprite.getColor();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			spriteArray[index].disappear();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			spriteArray[index].show(originalColor);
		}
	}


}

int main()
{
	texture.loadFromFile("PixelTexture.png");
	sf::Texture* texturePtr = &texture;

	for (CURRENT_SPRITE = 0; CURRENT_SPRITE < MAX_SPRITES; CURRENT_SPRITE++)
	{
		int* xPositionPtr = &xPositionsArray[CURRENT_SPRITE];
		int* yPositionPtr = &yPositionsArray[CURRENT_SPRITE];

		xPosition = rand() % window.getSize().x;
		xPositionPtr[CURRENT_SPRITE] = xPosition;

		yPosition = rand() % window.getSize().y;
		yPositionPtr[CURRENT_SPRITE] = yPosition;

		sprite.setTexture(*texturePtr);

		spriteArray.push_back(Player(*xPositionPtr, *yPositionPtr, sprite));
		spriteArray[CURRENT_SPRITE].setSpritePosition(*xPositionPtr, *yPositionPtr);
	}

	sf::Color originalColor = spriteArray[0]._sprite.getColor();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		movePlayer();
		changeColor();

		window.display();

	}

	return 0;
}

