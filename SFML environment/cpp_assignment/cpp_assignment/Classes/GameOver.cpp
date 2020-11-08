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
		while (getline(HighScoreData, line)) {
			highScores.push_back(std::stoi(line));
		}

		highScoreText.setString("Highscores: \n" + 
			std::to_string(highScores[0]) + "\n" +
			std::to_string(highScores[1]) + "\n" +
			std::to_string(highScores[2]) + "\n" +
			std::to_string(highScores[3]) + "\n" +
			std::to_string(highScores[4]));
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
	highScoreText.setCharacterSize(50);
	highScoreText.setPosition(sf::Vector2f(50, 400));
	highScoreText.setFillColor(sf::Color::Black);

	addTextObject(gameOverText);
	addTextObject(highScoreText);
}

void GameOver::handleButtons() {
	quitButton.setSize(sf::Vector2f(200, 50));
	quitButton.setPosition(sf::Vector2f(1710, 1020));
	quitButton.setString("Quit", m_font, 50, sf::Color::Black);

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