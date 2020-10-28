#include <SFML/graphics.hpp>

#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

#include "../Headers/main.h"

Character character;
Text witsText;
Text strengthText;
Text agilityText;

Font font;

Text menuText[3];

int yPosText = 65;
int xPosText = 1620;
int counter = 0;
int* counterPtr = &counter;

int m_strength = 100;
int m_agility = 100;
int m_wits = 100;

void nextScene() {
	counter++;
}

void backToMenu() {
	counter = 0;
}

void generateCharacter() {
	character.strength = character.GenerateValues(75, 100);
	character.agility = character.GenerateValues(75, 100);
	character.intelligence = character.GenerateValues(75, 100);

	witsText.setString(to_string(character.intelligence));
	strengthText.setString(to_string(character.strength));
	agilityText.setString(to_string(character.agility));
}

int main() {
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	Menu menuTest(window, font);
	Scene characterGen("characterGen");

	/*
	Scene menu("menu");
	Scene arena("arena");
	 */

	 /*menu.addGameObject(playButton);
	 menu.addGameObject(eraseButton);
	 menu.addGameObject(quitButtonMenu);
	 menu.addTextObject(title);
	 menu.addGameObject(background);

	 //Menu menu;
	 //scene1.addGameObject(menu);

	 Button generateButton(&generateCharacter);
	 generateButton.setSize(400, 200);
	 generateButton.setPosition(1500, 100);
	 generateButton.setColour(Color::Magenta);
	 generateButton.setString("Generate", font, 100, Color::White);

	 Button cancelButton(&backToMenu);
	 cancelButton.setSize(300, 130);
	 cancelButton.setPosition(100, 900);
	 cancelButton.setColour(Color::White);
	 cancelButton.setString("Cancel", font, 100, Color::Black);

	 Button fightButton(&nextScene);
	 fightButton.setSize(400, 200);
	 fightButton.setPosition(1500, 600);
	 fightButton.setColour(Color::Red);
	 fightButton.setString("PLAY", font, 150, Color::Black);

	 SpriteObject strengthIcon("strengthIcon", "strengthIcon.png");
	 strengthIcon.setPosition(sf::Vector2f(100, 500));
	 strengthIcon.setScale(sf::Vector2f(0.5f, 0.5f));
	 strengthText.setFont(font);
	 strengthText.setCharacterSize(100);
	 strengthText.setPosition(180, 760);
	 strengthText.setString(to_string(m_strength));

	 SpriteObject agilityIcon("agilityIcon", "agilityIcon.png");
	 agilityIcon.setPosition(sf::Vector2f(500, 500));
	 agilityIcon.setScale(sf::Vector2f(0.5f, 0.5f));
	 agilityText.setFont(font);
	 agilityText.setCharacterSize(100);
	 agilityText.setPosition(580, 760);
	 agilityText.setString(to_string(m_agility));

	 SpriteObject witsIcon("witsIcon", "witsIcon.png");
	 witsIcon.setPosition(sf::Vector2f(900, 500));
	 witsIcon.setScale(sf::Vector2f(0.5f, 0.5f));
	 witsText.setFont(font);
	 witsText.setCharacterSize(100);
	 witsText.setPosition(980, 760);
	 witsText.setString(to_string(m_wits));

	 generateButton();

	 characterGen.addGameObject(generateButton);
	 characterGen.addGameObject(cancelButton);
	 characterGen.addGameObject(fightButton);

	 characterGen.addGameObject(strengthIcon);
	 characterGen.addTextObject(strengthText);

	 characterGen.addGameObject(agilityIcon);
	 characterGen.addTextObject(agilityText);

	 characterGen.addGameObject(witsIcon);
	 characterGen.addTextObject(witsText);

	 Button quitButtonLevel(&backToMenu);
	 quitButtonLevel.setSize(200, 100);
	 quitButtonLevel.setPosition(1700, 900);
	 quitButtonLevel.setColour(Color::Blue);
	 quitButtonLevel.setString("Quit", font, 100, Color::White);

	 arena.addGameObject(quitButtonLevel);*/

	SceneHandler handler;
	handler.addScene(menuTest);
	handler.addScene(characterGen);
	//handler.addScene(arena);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			float mousePositionX = Mouse::getPosition(window).x;
			float mousePositionY = Mouse::getPosition(window).y;
			Vector2f mousePosition = Vector2f(mousePositionX, mousePositionY);

			if (counter == 0) {
				menuTest.checkInput(event, window, mousePosition, handler, counter);
			}

			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					/*if (menuTest.testButton.onClick(mousePosition) == true)
					{
						if (counter == 0) {
							handler.stackScene("characterGen");
							counter++;
						}
						else {
							handler.popScene();
							counter--;
						}
					}*/
					/*
					if (quitButtonMenu.onClick(mousePosition) == true && counter == 0) {
						window.close();
					}

					if (counter == 1) {
						if (cancelButton.onClick(mousePosition) == true) {
							if (counter == 1) {
								handler.stackScene("menu");
								counter = 0;
							}
							else {
								handler.popScene();
								counter++;
							}
						}

						if (fightButton.onClick(mousePosition) == true) {
							if (counter == 1) {
								handler.stackScene("arena");
								counter++;
								cout << counter;
							}
							else {
								handler.popScene();
								counter--;
							}
						}

						if (generateButton.onClick(mousePosition) == true) {
							generateButton();
						}
					}

					if (counter == 2) {
						if (quitButtonLevel.onClick(mousePosition) == true) {
							if (counter == 2) {
								handler.stackScene("menu");
								counter = 0;
							}
							else {
								handler.popScene();
								counter++;
							}
						}
					}*/
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