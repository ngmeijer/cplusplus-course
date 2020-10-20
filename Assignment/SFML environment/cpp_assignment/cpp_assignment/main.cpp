#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Menu.h"

using namespace std;

int xMouse;
int yMouse;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Arena game");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		menu.draw(window);

		menu.checkInput(window);

		window.display();
	}

	return 0;
}