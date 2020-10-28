//Libraries//
#include "SFML/Graphics.hpp"
#include <iostream>

//Header inclusion//
#include "../Headers/Menu.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/sceneHandler.hpp"

using namespace std;

Font m_font;

Text title;
SpriteObject background("background", "titleBG.jpg");
Button playButton;
Button eraseButton;
Button quitButton;

Menu::Menu() {}

Menu::Menu(RenderWindow& windowRef, Font& font) : Scene()
{
	m_font = font;

	handleText(windowRef);
	handleButtons();
	handleBackground();
}

Menu::~Menu()
{

}

void Menu::handleText(RenderWindow& window) {
	title.setFont(m_font);
	title.setCharacterSize(80);
	title.setPosition((window.getSize().x / 2 - 250), 50);
	title.setString("Nether Fights");

	addTextObject(title);
}

void Menu::handleButtons() {
	playButton;
	playButton.setSize(250, 100);
	playButton.setPosition(1600, 300);
	playButton.setColour(Color::Red);
	playButton.setString("Play", m_font, 100, Color::White);

	eraseButton.setSize(250, 100);
	eraseButton.setPosition(1600, 550);
	eraseButton.setColour(Color::Magenta);
	eraseButton.setString("Erase data", m_font, 50, Color::White);

	quitButton.setSize(250, 100);
	quitButton.setPosition(1600, 800);
	quitButton.setColour(Color::Blue);
	quitButton.setString("Quit", m_font, 100, Color::White);

	addGameObject(playButton);
	addGameObject(eraseButton);
	addGameObject(quitButton);
}

void Menu::handleBackground() {

	background.setPosition(sf::Vector2f(400, 200));
	background.setScale(sf::Vector2f(0.6f, 0.6f));

	addGameObject(background);
}

void Menu::defineButtons() {

}

void Menu::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (playButton.onClick(mousePos) == true) {
				handler.stackScene("characterGen");
				counter++;
			}
			/*else {
				handler.popScene();
			}*/

			if (quitButton.onClick(mousePos) == true) {
				window.close();
			}
		}
	}
}