//Libraries//
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>

//Header inclusion//
#include "../Headers/Menu.hpp"
#include "../Headers/Button.hpp"

using namespace std;

Text title;
SpriteObject background("background", "titleBG.jpg");

Button playButton;
Button eraseButton;
Button quitButtonMenu;

//std::ifstream characterFileMenu("PlayerData.txt");


Menu::Menu() {}

Menu::Menu(std::string identifier, RenderWindow& windowRef, Font& font) : Scene(identifier)
{
	m_font = font;

	handleBackground();
	handleText(windowRef);
	handleButtons();
}

Menu::~Menu() {  }

void Menu::handleText(RenderWindow& window) {
	title.setFont(m_font);
	title.setCharacterSize(60);
	title.setPosition((window.getSize().x / 2 - 500), 50);
	title.setString("Nether Fights");

	addTextObject(title);
}

void Menu::handleButtons() {
	playButton.setSize(sf::Vector2f(250, 100));
	playButton.setPosition(sf::Vector2f(1250, 190));
	playButton.setColour(Color::Transparent);
	playButton.setString("Play", m_font, 80, Color::White);

	eraseButton.setSize(sf::Vector2f(450, 100));
	eraseButton.setPosition(sf::Vector2f(1250, 440));
	eraseButton.setColour(Color::Transparent);
	eraseButton.setString("Erase data", m_font, 80, Color::White);

	quitButtonMenu.setSize(sf::Vector2f(250, 100));
	quitButtonMenu.setPosition(sf::Vector2f(1250, 690));
	quitButtonMenu.setColour(Color::Transparent);
	quitButtonMenu.setString("Quit", m_font, 80, Color::White);

	addGameObject(playButton);
	addGameObject(eraseButton);
	addGameObject(quitButtonMenu);
}

void Menu::handleBackground() {

	background.setScale(sf::Vector2f(1.0f, 1.0f));

	addGameObject(background);
}

void Menu::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (playButton.onClick(mousePos) == true) {
				handler.stackScene("character");
				counter++;
			}

			if (quitButtonMenu.onClick(mousePos) == true) {
				window.close();
			}

			if (eraseButton.onClick(mousePos) == true) {
				/*cout << "erased data!" << endl;
				if (!characterFileMenu.is_open() || characterFileMenu.fail())
				{
					characterFileMenu.close();
					cout << "\t\t\t Error : failed to erase file content!" << endl;
				}
				characterFileMenu.close();*/
			}
		}
	}
}