//Libraries//
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>

//Header inclusion//
#include "../Headers/Button.hpp"
#include "../Headers/scene.hpp"
#include "../Headers/GameOver.hpp"

Button quitButton;
SpriteObject backgroundGO("background", "Assets/GameOverBackground.jpg");
sf::Text gameOverText;
sf::Text highScoreText;
sf::Text highScoresElements;
sf::Text scoreDescription;

std::ifstream HighScoreData("HighscoreData.txt");
std::vector<int> highScores;

GameOver::GameOver() {}

GameOver::GameOver(std::string identifier, sf::RenderWindow& windowRef, sf::Font& font) : Scene(identifier)
{
	m_font = font;

	handleBackground();
	handleButtons();
	handleText();

	if (HighScoreData.is_open())
	{
		std::string line;
		while (getline(HighScoreData, line) && (highScores.size() < 6)) {
			if (!line.empty()) {
				highScores.push_back(std::stoi(line));
			}
			else {
				highScoresElements.setString("No highscores available.");
				return;
			}
		}

		for (int i = 0; i < highScores.size(); i++) {
			std::string oldString = highScoresElements.getString();
			highScoresElements.setString(oldString + "\n" + std::to_string(highScores[i]));
		}
	}
	else std::cout << "Unable to open file";
}

GameOver::~GameOver() {  }

void GameOver::handleText() {
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(250);
	gameOverText.setFont(m_font);
	gameOverText.setPosition(sf::Vector2f(200, 20));
	gameOverText.setFillColor(sf::Color::Black);

	highScoreText.setString("Highscores:");
	highScoreText.setFont(m_font);
	highScoreText.setCharacterSize(75);
	highScoreText.setPosition(sf::Vector2f(50, 400));
	highScoreText.setFillColor(sf::Color::Red);

	highScoresElements.setFont(m_font);
	highScoresElements.setCharacterSize(50);
	highScoresElements.setPosition(sf::Vector2f(50, 500));
	highScoresElements.setFillColor(sf::Color::Black);

	scoreDescription.setString("Lower is better");
	scoreDescription.setFont(m_font);
	scoreDescription.setCharacterSize(50);
	scoreDescription.setPosition(sf::Vector2f(50, 500));
	scoreDescription.setFillColor(sf::Color::Black);

	addTextObject(scoreDescription);
	addTextObject(gameOverText);
	addTextObject(highScoreText);
	addTextObject(highScoresElements);
}

void GameOver::handleButtons() {
	quitButton.setSize(sf::Vector2f(350, 200));
	quitButton.setPosition(sf::Vector2f(760, 800));
	quitButton.setString("Quit", m_font, 150, sf::Color::Red);
	quitButton.setColour(sf::Color::Transparent);

	addGameObject(quitButton);
}

void GameOver::handleBackground() {
	addGameObject(backgroundGO);
}

void GameOver::checkInput(sf::Event event, sf::RenderWindow& window, sf::Vector2f mousePos, SceneHandler& handler, int& counter)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (quitButton.onClick(mousePos) == true) {
				handler.stackScene("menu");
				counter = 0;
			}
		}
	}
}