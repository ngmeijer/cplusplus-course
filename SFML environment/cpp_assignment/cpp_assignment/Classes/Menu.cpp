//Libraries//
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Header inclusion//
#include "../Headers/Menu.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/GameOver.hpp"

using namespace std;

typedef sf::Text TextObject;
typedef std::string StringObject;
typedef sf::RectangleShape RectShape;
typedef std::ifstream InputFile;

Text title;
SpriteObject background("background", "Assets/titleBG.jpg");

Button playButton;
Button eraseButton;
Button quitButtonMenu;

InputFile characterFileMenu("Save data/PlayerData.cmgt");
InputFile highScores("Save data/HighscoreData.cmgt");
std::vector<int> highScoreVec;
TextObject highscoreTitle;
TextObject highscoreText;
TextObject highscoreDescription;

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

	highscoreTitle.setFont(m_font);
	highscoreTitle.setCharacterSize(75);
	highscoreTitle.setPosition(10, 400);
	highscoreTitle.setString("Highscore: ");

	highscoreDescription.setFont(m_font);
	highscoreDescription.setCharacterSize(50);
	highscoreDescription.setPosition(10, 485);
	highscoreDescription.setString("Lower is better");

	highscoreText.setFont(m_font);
	highscoreText.setCharacterSize(40);
	highscoreText.setPosition(10, 550);

	addTextObject(highscoreTitle);
	addTextObject(highscoreDescription);
	addTextObject(highscoreText);
	addTextObject(title);
}

void Menu::handleHighScore() {
	if (highScores.is_open())
	{
		std::string line;
		while (getline(highScores, line) && (highScoreVec.size() < 6)) {
			if (std::stoi(line) != 0) {
				highScoreVec.push_back(std::stoi(line));
				sort(highScoreVec.begin(), highScoreVec.end());
			}
		}

		if (highScoreVec.size() > 0) {
			for (int i = 0; i < highScoreVec.size(); i++) {
				std::string oldString = highscoreText.getString();
				highscoreText.setString(oldString + std::to_string(highScoreVec[i]) + "\n");
			}
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
				std::ofstream playerDataFile("Save data/PlayerData.cmgt");
				if (playerDataFile.is_open()) {
					playerDataFile << 3 << std::endl;
					playerDataFile << 3 << std::endl;
					playerDataFile << 3 << std::endl;

					playerDataFile << 9;

					playerDataFile.close();
				}

				std::ofstream highscoreFile("Save data/HighscoreData.cmgt", std::ios::trunc);
				if (highscoreFile.is_open()) {
					highscoreFile << 0 << std::endl;
					highscoreText.setString("No current highscores");

					highscoreFile.close();
				}
			}
		}
	}
}