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

using namespace std;
using namespace sf;

enum MOVEMENT_SWITCH {
	MOVE_LEFT = sf::Keyboard::A,
	MOVE_RIGHT = sf::Keyboard::D,
	MOVE_UP = sf::Keyboard::W,
	MOVE_DOWN = sf::Keyboard::S
};

Keyboard::Key currentKey;
int currentKeyIndex;
Color originalColor;

float moveVelocity = 1000000.0f;

bool movingLeft = false;
bool movingRight = false;
bool movingUp = false;
bool movingDown = false;

RenderWindow window(sf::VideoMode(1000, 1000), "SFML_visual");
const int MAX_SPRITES = 7;

int randomXosition;

Texture texture;
Sprite sprite;
int xPositionsArray[MAX_SPRITES];
int yPositionsArray[MAX_SPRITES];
float xPosition;
float yPosition;
vector<Player> spriteArray;
vector<Vector2f> movementHistory;
unsigned int CURRENT_SPRITE;
int movementX = 0;
int movementY = 0;

Vector2f velocity(0.0f, 0.0f);
Vector2f acceleration(moveVelocity, moveVelocity);

Event event;

bool CurrentKeyState[sf::Keyboard::KeyCount];
bool PreviousKeyState[sf::Keyboard::KeyCount];

bool KeyReleased(sf::Keyboard::Key Key);

MOVEMENT_SWITCH moveSwitch;

void drawPlayer() {
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
}

void movePlayer() {
	Clock clock;
	clock.restart();
	float deltaTime = clock.restart().asSeconds();

	for (unsigned int index = 0; index < MAX_SPRITES; index++) {

		int* xPositionsArrayPtr = &xPositionsArray[index];
		int* yPositionsArrayPtr = &yPositionsArray[index];

		window.draw(spriteArray[index]._sprite);

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr -= (velocity.x = acceleration.x * deltaTime), *yPositionsArrayPtr);
			currentKey == Keyboard::A;
			currentKeyIndex = 0;
			movementX += (velocity.x / MAX_SPRITES);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr += (velocity.x = acceleration.x * deltaTime), *yPositionsArrayPtr);
			currentKey == Keyboard::D;
			currentKeyIndex = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr, *yPositionsArrayPtr += (velocity.y = acceleration.y * deltaTime));
			currentKey == Keyboard::S;
			currentKeyIndex = 18;

		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			spriteArray[index].setSpritePosition(*xPositionsArrayPtr, *yPositionsArrayPtr -= (velocity.y = acceleration.y * deltaTime));
			currentKey == Keyboard::W;
			currentKeyIndex = 22;
		}
	}
}

bool KeyReleased(Keyboard::Key key) {
	return (!CurrentKeyState[key] && PreviousKeyState[key]);
}

void trackMovement() {
	for (unsigned int i = 0; i < Keyboard::KeyCount; ++i) {
		PreviousKeyState[i] = CurrentKeyState[i];

		CurrentKeyState[i] = Keyboard::isKeyPressed((Keyboard::Key)i);
	}
}

void changeColor() {
	for (int index = 0; index < MAX_SPRITES; index++) {

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
	drawPlayer();

	originalColor = spriteArray[0]._sprite.getColor();

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
		trackMovement();
		changeColor();

		window.display();

	}

	return 0;
}

