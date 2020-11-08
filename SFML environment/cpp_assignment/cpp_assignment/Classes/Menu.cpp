//Libraries//
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Header inclusion//
#include "../Headers/Menu.hpp"
#include "../Headers/Button.hpp"

using namespace std;

Text title;
SpriteObject background("background", "Assets/titleBG.jpg");

Button playButton;
Button eraseButton;
Button quitButtonMenu;

std::ifstream characterFileMenu("PlayerData.txt");
std::ifstream highScores("HighscoreData.txt");
std::vector<int> highScoreVec;
sf::Text highScoreTitle;
sf::Text highscoreText;

Menu::Menu() {}

Menu::Menu(std::string identifier, RenderWindow& windowRef, Font& font) : Scene(identifier)
{
	m_font = font;

	handleBackground();
	handleText();
	handleButtons();
	handleHighScore();
}

Menu::~Menu() {  }

void Menu::handleText() {
	title.setFont(m_font);
	title.setCharacterSize(270);
	title.setPosition(10, -20);
	title.setString("Nether Fights");

	highScoreTitle.setFont(m_font);
	highScoreTitle.setCharacterSize(75);
	highScoreTitle.setPosition(10, 400);
	highScoreTitle.setString("Highscore:");

	highscoreText.setFont(m_font);
	highscoreText.setCharacterSize(40);
	highscoreText.setPosition(10, 500);

	addTextObject(highScoreTitle);
	addTextObject(highscoreText);
	addTextObject(title);
}

void Menu::handleHighScore() {
	if (highScores.is_open())
	{
		std::string line;
		while (getline(highScores, line)) {
			highScoreVec.push_back(std::stoi(line));
		}

		if (line.empty()) {
			highscoreText.setString("No highscores available");
		}
		else {
			highscoreText.setString(
				std::to_string(highScoreVec[0]) + "\n" +
				std::to_string(highScoreVec[1]) + "\n" +
				std::to_string(highScoreVec[2]) + "\n" +
				std::to_string(highScoreVec[3]) + "\n" +
				std::to_string(highScoreVec[4]));
		}
	}
	else std::cout << "Unable to open file";

	addTextObject(highscoreText);
}

void Menu::handleButtons() {
	playButton.setSize(sf::Vector2f(500, 220));
	playButton.setPosition(sf::Vector2f(50, 830));
	playButton.setColour(Color::Transparent);
	playButton.setString("Play", m_font, 200, Color::White);

	eraseButton.setSize(sf::Vector2f(600, 130));
	eraseButton.setPosition(sf::Vector2f(1190, 690));
	eraseButton.setColour(Color::Transparent);
	eraseButton.setString("Erase data", m_font, 100, Color::White);

	quitButtonMenu.setSize(sf::Vector2f(250, 120));
	quitButtonMenu.setPosition(sf::Vector2f(1550, 890));
	quitButtonMenu.setColour(Color::Transparent);
	quitButtonMenu.setString("Quit", m_font, 100, Color::White);

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
				characterFileMenu.open("PlayerData.txt", std::ofstream::out | std::ofstream::trunc);

				characterFileMenu.close();

				std::ofstream highscoreFile("HighscoreData.txt", std::ostream::out | std::ofstream::trunc);
				if (highscoreFile.is_open()) {
					std::cout << "writing to file";
					highscoreFile << "No current highscores" << "\n";
				}

				handleHighScore();
			}
		}
	}
}