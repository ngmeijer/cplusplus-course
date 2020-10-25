//Libraries//
#include <SFML/Graphics.hpp>
#include <iostream>

//Header inclusion//
#include "../Headers/Menu.hpp"
#include "../Headers/Button.hpp"

using namespace std;
using namespace sf;

RectangleShape selectionRect;
RectangleShape selectionRect2;

int xPos = 1150;
int yPos = -200;

//Play button
int playButtonLeft;
int playButtonRight;
int playButtonTop;
int playButtonBottom;

int playButtonWidth;
int playButtonHeight;

//Erase data button
int eraseButtonLeft;
int eraseButtonRight;
int eraseButtonTop;
int eraseButtonBottom;

int eraseButtonWidth;
int eraseButtonHeight;

//Quit button
int quitButtonLeft;
int quitButtonRight;
int quitButtonTop;
int quitButtonBottom;

int quitButtonWidth;
int quitButtonHeight;

Menu::Menu() {}

Menu::Menu(float width, float height)
{
	Scene mainMenu;

	if (!font.loadFromFile("font.ttf")) {
		cout << "Couldn't load font." << endl;
	}

	for (int index = 0; index < maxText; index++)
	{
		menuText[index].setFont(font);
		menuText[index].setCharacterSize(100);
		menuText[index].setOutlineColor(Color::White);
		yPos += 350;
		menuText[index].setPosition(xPos, yPos);
		menuText[index].setOrigin(menuText[index].getLocalBounds().width / 2, menuText[index].getLocalBounds().height / 2);
	}

	Button playButton;
	playButton.setSize(200, 100);
	playButton.setString("Play", font, 100, Color::Red);


	menuText[0].setString("Play");
	menuText[1].setString("Erase Data");
	menuText[2].setString("Quit");


	playButtonWidth = menuText[0].getLocalBounds().width;
	playButtonHeight = menuText[0].getLocalBounds().height;

	eraseButtonWidth = menuText[1].getLocalBounds().width;
	eraseButtonHeight = menuText[1].getLocalBounds().height;

	quitButtonWidth = menuText[2].getLocalBounds().width;
	quitButtonHeight = menuText[2].getLocalBounds().height;

	defineButtons();

	selectionRect.setSize(Vector2f(playButtonWidth, playButtonHeight));
	selectionRect.setPosition(Vector2f(menuText[0].getGlobalBounds().left, menuText[0].getGlobalBounds().top));
	selectionRect.setFillColor(Color::Transparent);

	selectionRect2.setSize(Vector2f(quitButtonWidth, quitButtonHeight));
	selectionRect2.setPosition(Vector2f(menuText[2].getGlobalBounds().left, menuText[2].getGlobalBounds().top));
	selectionRect2.setFillColor(Color::Transparent);
	selectionRect2.setScale(Vector2f(1.3, 1.3));
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

	//Erase data button
	eraseButtonLeft = menuText[1].getGlobalBounds().left;
	eraseButtonTop = menuText[1].getGlobalBounds().top;

	eraseButtonRight = (eraseButtonLeft + eraseButtonWidth);
	eraseButtonBottom = (eraseButtonTop + eraseButtonHeight);

	//Quit button
	quitButtonLeft = menuText[2].getGlobalBounds().left;
	quitButtonTop = menuText[2].getGlobalBounds().top;

	quitButtonRight = (quitButtonLeft + quitButtonWidth);
	quitButtonBottom = (quitButtonTop + quitButtonHeight);
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