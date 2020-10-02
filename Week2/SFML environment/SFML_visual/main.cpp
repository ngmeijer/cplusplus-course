#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class PlayerSprite
{
public:
	int _xPosition;
	int _yPosition;
	sf::Sprite _sprite;
	sf::Texture texture;

	PlayerSprite(int x, int y, sf::Sprite sprite) {
		_xPosition = x;
		_yPosition = y;
		_sprite = sprite;
		texture.loadFromFile("PixelTexture.png");
		sprite.setTexture(texture);
	}

	void setSpritePosition(int xPosition, int yPosition) {
		_sprite.setPosition(xPosition, yPosition);
	}

	double* normalizeMoveSpeed(sf::Vector2<float> axisPosition) {
		double length = sqrt((axisPosition.x * axisPosition.x) + (axisPosition.y * axisPosition.y));
		return &length;
	}

	void disappear() {
		sf::Color originalColor = _sprite.getColor();
		if (_sprite.getColor() != sf::Color::Transparent)
			_sprite.setColor(sf::Color::Transparent);
	}

	void show(sf::Color color) {
		_sprite.setColor(color);
	}
};

float moveVelocity = 1000000.0f;

bool movingLeft = false;
bool movingRight = false;
bool movingUp = false;
bool movingDown = false;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML_visual");
const int MAX_SPRITES = 5;

int randomXosition;

using namespace std;

sf::Texture texture;
sf::Sprite sprite;
int xPositionsArray[MAX_SPRITES];
int yPositionsArray[MAX_SPRITES];
float xPosition;
float yPosition;
vector<PlayerSprite> spriteArray;
int CURRENT_SPRITE;

int main()
{
	sf::Vector2f velocity(0.0f, 0.0f);
	sf::Vector2f acceleration(moveVelocity, moveVelocity);

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

		spriteArray.push_back(PlayerSprite(*xPositionPtr, *yPositionPtr, sprite));
		spriteArray[CURRENT_SPRITE].setSpritePosition(*xPositionPtr, *yPositionPtr);
	}

	sf::Color originalColor = spriteArray[0]._sprite.getColor();

	while (window.isOpen())
	{
		sf::Clock clock;
		clock.restart();
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		for (int index = 0; index < MAX_SPRITES; index++) {
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				spriteArray[index].disappear();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				spriteArray[index].show(originalColor);
			}
		}
		window.display();

	}

	return 0;
}

