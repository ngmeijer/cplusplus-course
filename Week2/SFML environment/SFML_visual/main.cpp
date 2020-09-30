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

using namespace std;

float xPosition;
float yPosition;

float moveSpeed = 0.1f;

bool movingLeft = false;
bool movingRight = false;
bool movingUp = false;
bool movingDown = false;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML_visual");
sf::Texture texture;
const int MAX_SPRITES = 2;
PlayerSprite spriteArray[MAX_SPRITES];
int randomXosition;

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
		texture.loadFromFile("PixelTexture.png");
	}
};

int main()
{
	srand(time(0));
	for (int CURRENT_SPRITE = 0; CURRENT_SPRITE < MAX_SPRITES; CURRENT_SPRITE++)
	{
		xPosition = rand() % 900 + 100;

		spriteArray[CURRENT_SPRITE].
			spriteArray[CURRENT_SPRITE].setPosition(((window.getSize().y) / 2), (window.getSize().y) / 2);
		xPosition = spriteArray[CURRENT_SPRITE].getPosition().x;
		yPosition = spriteArray[CURRENT_SPRITE].getPosition().y;

		cout << xPosition << endl;
	}



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int CURRENT_SPRITE = 0; CURRENT_SPRITE < MAX_SPRITES; CURRENT_SPRITE++) {

			window.clear();
			window.draw(spriteArray[CURRENT_SPRITE]);
			window.display();

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
				spriteArray[CURRENT_SPRITE].setColor(sf::Color::Red);
		}
	}

	return 0;
}


