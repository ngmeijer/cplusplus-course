#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Texture playButtonTexture;
Sprite playButtonSprite;

RectangleShape selectionRect;
RectangleShape selectionRect2;

int xPos = 400;
int yPos;

//Play button
int playButtonLeft;
int playButtonRight;
int playButtonTop;
int playButtonBottom;

int playButtonWidth;
int playButtonHeight;

//Quit button
int quitButtonLeft;
int quitButtonRight;
int quitButtonTop;
int quitButtonBottom;

int quitButtonWidth;
int quitButtonHeight;

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font.ttf")) {
		cout << "Couldn't load font." << endl;
	}

	for (int index = 0; index < maxText; index++)
	{
		menuText[index].setFont(font);
		menuText[index].setCharacterSize(100);
		menuText[index].setOutlineColor(Color::White);
		yPos += 200;
		menuText[index].setPosition(xPos, yPos);
		menuText[index].setOrigin(menuText[index].getLocalBounds().width / 2, menuText[index].getLocalBounds().height / 2);
	}


	menuText[0].setString("Play");
	menuText[1].setString("Quit");


	playButtonWidth = menuText[0].getLocalBounds().width;
	playButtonHeight = menuText[0].getLocalBounds().height;

	quitButtonWidth = menuText[1].getLocalBounds().width;
	quitButtonHeight = menuText[1].getLocalBounds().height;

	defineButtons();

	selectionRect.setSize(Vector2f(playButtonWidth, playButtonHeight));
	selectionRect.setPosition(Vector2f(menuText[0].getGlobalBounds().left, menuText[0].getGlobalBounds().top));
	selectionRect.setFillColor(Color::Transparent);

	selectionRect2.setSize(Vector2f(quitButtonWidth, quitButtonHeight));
	selectionRect2.setPosition(Vector2f(menuText[1].getGlobalBounds().left, menuText[1].getGlobalBounds().top));
	selectionRect2.setFillColor(Color::Transparent);
}

Menu::~Menu()
{

}

void Menu::draw(RenderWindow& window)
{
	window.draw(selectionRect);
	window.draw(selectionRect2);

	for (int i = 0; i < maxText; i++) {
		window.draw(menuText[i]);
	}
}

void Menu::defineButtons() {
	//Play button
	playButtonLeft = menuText[0].getGlobalBounds().left;
	playButtonTop = menuText[0].getGlobalBounds().top;

	playButtonRight = (playButtonLeft + playButtonWidth);
	playButtonBottom = (playButtonTop + playButtonHeight);

	//Quit button
	quitButtonLeft = menuText[1].getGlobalBounds().left;
	quitButtonTop = menuText[1].getGlobalBounds().top;

	quitButtonRight = (quitButtonLeft + quitButtonWidth);
	quitButtonBottom = (quitButtonTop + quitButtonHeight);
}

void Menu::calculateButtonBorders(int index, int x1, int y1, int x2, int y2, int width, int height) {
	x1 = menuText[index].getGlobalBounds().left;
	y1 = menuText[index].getGlobalBounds().top;

	width = menuText[index].getLocalBounds().width;
	height = menuText[index].getLocalBounds().height;

	x2 = (x1 + width);
	y2 = (y1 + height);
	cout << x1 << endl;
}

void Menu::checkInput(RenderWindow& window)
{
	int xMouse = Mouse::getPosition(window).x;
	int yMouse = Mouse::getPosition(window).y;

	if ((xMouse > playButtonLeft) && (xMouse < playButtonRight))
	{
		if ((yMouse > playButtonTop) && (yMouse < playButtonBottom))
		{
			selectionRect.setPosition(Vector2f(playButtonLeft, playButtonTop));
			selectionRect.setFillColor(Color::Red);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				cout << "clicked play!" << endl;
			}
		}
		else selectionRect.setFillColor(Color::Transparent);
	}

	if ((xMouse > quitButtonLeft) && (xMouse < quitButtonRight))
	{
		if ((yMouse > quitButtonTop) && (yMouse < quitButtonBottom))
		{
			selectionRect2.setPosition(Vector2f(quitButtonLeft, quitButtonTop));
			selectionRect2.setFillColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				window.close();
			}
		}
		else selectionRect2.setFillColor(Color::Transparent);
	}
}