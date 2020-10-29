#include <iostream>

#include "../Headers/Arena.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

Button attackButton;
Button prepareButton;
Button recoverButton;
Button magicButton;
Button quitButtonArena;

Arena::Arena() { }

Arena::Arena(std::string identifier, sf::RenderWindow& windowRef, sf::Font& fontRef) : Scene(identifier)
{
	m_font = fontRef;

	handleBackground();
	handleButtons();
	handleText(windowRef);
}

Arena::~Arena() { }

void Arena::handleText(RenderWindow& window) {

}

void Arena::handleButtons() {
	attackButton.setSize(200, 100);
	attackButton.setPosition(400, 900);
	attackButton.setColour(Color::Transparent);
	attackButton.setString("Attack", m_font, 30, Color::White);

	prepareButton.setSize(200, 100);
	prepareButton.setPosition(700, 900);
	prepareButton.setColour(Color::Transparent);
	prepareButton.setString("Prepare", m_font, 30, Color::White);

	recoverButton.setSize(200, 100);
	recoverButton.setPosition(1000, 900);
	recoverButton.setColour(Color::Transparent);
	recoverButton.setString("Recover", m_font, 30, Color::White);

	magicButton.setSize(200, 100);
	magicButton.setPosition(1300, 900);
	magicButton.setColour(Color::Transparent);
	magicButton.setString("Cast Magic", m_font, 30, Color::White);

	quitButtonArena.setSize(200, 100);
	quitButtonArena.setPosition(1700, 1000);
	quitButtonArena.setColour(Color::Transparent);
	quitButtonArena.setString("Quit", m_font, 50, Color::White);

	addGameObject(attackButton);
	addGameObject(prepareButton);
	addGameObject(recoverButton);
	addGameObject(magicButton);
	addGameObject(quitButtonArena);
}

void Arena::handleBackground() {
	/*addGameObject(background2);*/
}

void Arena::checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (quitButtonArena.onClick(mousePos) == true) {
				handler.stackScene("menu");
				counter = 0;
			}
		}
	}
}