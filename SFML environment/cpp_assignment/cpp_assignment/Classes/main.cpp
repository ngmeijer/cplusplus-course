#include <SFML/graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/CharScene.hpp"
#include "../Headers/Arena.hpp"
#include "../Headers/GameOver.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

#include "../Headers/main.h"

#include <fstream>

std::ifstream characterData("Save data/PlayerData.cmgt");
sf::Music backgroundMusic;

Font font;
bool hasImportedPlayer = false;
bool hasRefreshedHighscore = false;
int counter = 0;
int* counterPtr = &counter;

std::vector<int> statsVec;

struct CharacterStats
{
	int strength;
	int agility;
	int intelligence;
	int availablePoints;
};

CharacterStats charStats;

void nextScene() {
	counter++;
}

void backToMenu() {
	counter = 0;
}

void readWritePlayerData() {
	if (characterData.fail()) {
		std::cout << "\n" << "Failed opening the PlayerData.cmgt file in main.cpp." << std::endl << "\n";
	}
	else {
		std::string line;
		while (getline(characterData, line)) {
			statsVec.push_back(std::stoi(line));
		}
		characterData.close();
	}

	charStats.strength = statsVec[0];
	charStats.agility = statsVec[1];
	charStats.intelligence = statsVec[2];
	charStats.availablePoints = statsVec[3];
}

void handleAudio() {
	if (!backgroundMusic.openFromFile("Assets/BackgroundMusic.wav")) {
		std::cout << "Could not find the background track." << std::endl;
		return;
	}
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(50.0f);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "NETHER FIGHTS!");

	readWritePlayerData();
	//handleAudio();

	if (!font.loadFromFile("Assets/font.ttf")) {
		std::cout << "Missing font." << std::endl;
	}

	Menu menu("menu", window, font);
	CharScene characterGen("character", font);
	Arena arena("arena", window, font);
	GameOver gameOver("gameover", window, font);

	SceneHandler handler;
	handler.addScene(menu);
	handler.addScene(characterGen);
	handler.addScene(arena);
	handler.addScene(gameOver);

	characterGen.importCharacter();

	while (window.isOpen()) {
		{
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				float mousePositionX = Mouse::getPosition(window).x;
				float mousePositionY = Mouse::getPosition(window).y;
				Vector2f mousePosition = Vector2f(mousePositionX, mousePositionY);

				switch (counter) {
				case 0:
					menu.checkInput(event, window, mousePosition, handler, counter);
					break;
				case 1:
					characterGen.checkInput(event, mousePosition, handler, counter);
					break;
				case 2:
					if (!hasImportedPlayer) {
						arena.importCharacter();
						arena.updateSkills();
						hasImportedPlayer = true;
					}
					arena.checkInput(event, window, mousePosition, handler, counter);
					break;
				case 3:
					if (!hasRefreshedHighscore) {
						gameOver.handleHighscores();
						hasRefreshedHighscore = true;
					}
					gameOver.checkInput(event, window, mousePosition, handler, counter);
				}
			}
		}
		window.clear();
		handler.update();
		handler.render(window);
		window.display();
	}
	return 0;
}