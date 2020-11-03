#include <SFML/graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/CharScene.hpp"
#include "../Headers/Arena.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

#include "../Headers/main.h"

#include <fstream>

std::ifstream characterData("PlayerData.txt");

Font font;

int counter = 0;
int* counterPtr = &counter;

Character character;

std::vector<int> statsVec;

struct CharacterStats
{
	int strength;
	int agility;
	int intelligence;
};

CharacterStats charStats;

void nextScene() {
	counter++;
}

void backToMenu() {
	counter = 0;
}

int main() {
	//Necessary for seeding the RNG. Currently disabled that.
	//srand(time(0));

	if (characterData.fail()) {
		std::cout << "\n" << "Failed opening the PlayerData.txt file." << endl << "\n";
	}
	else {
		string line;
		while (getline(characterData, line)) {
			statsVec.push_back(std::stoi(line));
		}
		characterData.close();
	}

	character.m_strength = statsVec[0];
	character.m_agility = statsVec[1];
	character.m_intelligence = statsVec[2];

	for (int i = 0; i < statsVec.size(); i++) {
		cout << "current: " << statsVec[i] << endl;
	}

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	Menu menu("menu", window, font);
	CharScene characterGen("character", font);
	Arena arena("arena", window, font);

	characterGen.importCharacter(character.m_strength, character.m_agility, character.m_intelligence);
	arena.importCharacter(character.m_strength, character.m_agility, character.m_intelligence);

	SceneHandler handler;
	handler.addScene(menu);
	handler.addScene(characterGen);
	handler.addScene(arena);

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
					arena.checkInput(event, window, mousePosition, handler, counter);
					break;
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