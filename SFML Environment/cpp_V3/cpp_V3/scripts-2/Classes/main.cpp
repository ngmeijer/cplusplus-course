#include <SFML/graphics.hpp>

#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"

Font font;

Text menuText[3];

int yPosText = 65;
int xPosText = 1620;
int counter = 0;
int* counterPtr = &counter;

int health = 100;

void nextScene() {
	counter++;
	cout << *counterPtr << endl;
}

void generateCharacter() {

}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	Scene menu("menu");
	Scene character("character");
	Scene fight("fight");

	Button playButton(&nextScene);
	playButton.setSize(250, 100);
	playButton.setPosition(1600, 300);
	playButton.setColour(Color::Red);
	playButton.setString("Play", font, 100, Color::White);

	Button quitButton;
	quitButton.setSize(250, 100);
	quitButton.setPosition(1600, 550);
	quitButton.setColour(Color::Magenta);
	quitButton.setString("Quit", font, 100, Color::White);

	Button eraseButton;
	eraseButton.setSize(250, 100);
	eraseButton.setPosition(1600, 800);
	eraseButton.setColour(Color::Blue);
	eraseButton.setString("Quit", font, 100, Color::White);


	menu.addGameObject(playButton);
	menu.addGameObject(eraseButton);
	menu.addGameObject(quitButton);

	//Menu menu;
	//scene1.addGameObject(menu);

	Button generateButton;
	generateButton.setSize(400, 200);
	generateButton.setPosition((window.getSize().x / 2 - generateButton.getSize().x / 2), (window.getSize().y / 2 - generateButton.getSize().y / 2));
	generateButton.setColour(Color::Magenta);
	generateButton.setString("Generate", font, 100, Color::White);

	Text health;
	health.setString("Health: " + health.getString());

	character.addGameObject(generateButton);
	character.addTextObject(health);

	SceneHandler handler;
	handler.addScene(menu);
	handler.addScene(character);
	handler.addScene(fight);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				float mousePositionX = Mouse::getPosition(window).x;
				float mousePositionY = Mouse::getPosition(window).y;
				Vector2f mousePosition = Vector2f(mousePositionX, mousePositionY);

				if (event.mouseButton.button == Mouse::Left) {
					if (playButton.onClick(mousePosition)) {
						handler.stackScene("character");
						playButton();
					}
					else {
						counter--;
						handler.popScene();
					}
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





