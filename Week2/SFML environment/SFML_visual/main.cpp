#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <ctime>

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

	void setPosition(int xPosition, int yPosition) {
		_sprite.setPosition(xPosition, yPosition);
	}
};

float xPositionArray;
float yPosition;

float moveSpeed = 0.1f;

bool movingLeft = false;
bool movingRight = false;
bool movingUp = false;
bool movingDown = false;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML_visual");
const int MAX_SPRITES = 6;

int randomXosition;

using namespace std;

sf::Texture texture;
sf::Sprite sprite;
int xPositionsArray[MAX_SPRITES];
int yPositionsArray[MAX_SPRITES];
vector<PlayerSprite> spriteArray;

int main()
{
	window.clear();
	texture.loadFromFile("PixelTexture.png");
	sprite.setTexture(texture);
	for (int CURRENT_SPRITE = 0; CURRENT_SPRITE < MAX_SPRITES; CURRENT_SPRITE++)
	{
		int xPosition = rand() % window.getSize().x - 100;
		xPositionsArray[CURRENT_SPRITE] = xPosition;

		int yPosition = rand() % window.getSize().y - 100;
		yPositionsArray[CURRENT_SPRITE] = yPosition;

		cout << xPosition << endl;
		spriteArray.push_back(PlayerSprite(200, 50, sprite));
		spriteArray[CURRENT_SPRITE].setPosition(xPositionsArray[CURRENT_SPRITE], yPositionsArray[CURRENT_SPRITE]);
		window.draw(spriteArray[CURRENT_SPRITE]._sprite);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.display();

		for (int CURRENT_SPRITE = 0; CURRENT_SPRITE < MAX_SPRITES; CURRENT_SPRITE++) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				spriteArray[CURRENT_SPRITE].setPosition(xPositionArray -= moveSpeed, yPosition);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				spriteArray[CURRENT_SPRITE].setPosition(xPositionArray += moveSpeed, yPosition);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				spriteArray[CURRENT_SPRITE].setPosition(xPositionArray, yPosition += moveSpeed);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				spriteArray[CURRENT_SPRITE].setPosition(xPositionArray, yPosition -= moveSpeed);

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				spriteArray[CURRENT_SPRITE].setColor(sf::Color::Transparent);
			}
			else
				sprite.setColor(sf::Color::Red);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					spriteArray[CURRENT_SPRITE].setPosition(xPosition -= moveSpeed, yPosition);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					spriteArray[CURRENT_SPRITE].setPosition(xPosition += moveSpeed, yPosition);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					spriteArray[CURRENT_SPRITE].setPosition(xPosition, yPosition += moveSpeed);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					spriteArray[CURRENT_SPRITE].setPosition(xPosition, yPosition -= moveSpeed);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					spriteArray[CURRENT_SPRITE].setColor(sf::Color::Transparent);
				}
				else
					spriteArray[CURRENT_SPRITE].setColor(sf::Color::Red);*/
		}
	}

	return 0;
}


