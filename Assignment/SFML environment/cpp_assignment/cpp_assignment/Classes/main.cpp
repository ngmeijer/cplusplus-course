#include <SFML/Graphics.hpp>

#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"

Font font;

Text menuText[3];
int yPosText;
int xPosText;

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	Scene scene1("menu");

	Button playButton;
	Text playText;
	playButton.setSize(200, 100);
	playButton.setPosition(1600, 300);
	playButton.setColour(Color::Red);
	playButton.setString("Play", font, 100, Color::White);
	playText.setString("Play");
	playText.setPosition(1600, 300);

	Button quitButton;
	quitButton.setSize(200, 100);
	quitButton.setPosition(1600, 550);
	quitButton.setColour(Color::Yellow);
	quitButton.setString("Quit", font, 100, Color::White);

	Button eraseButton;
	eraseButton.setSize(200, 100);
	eraseButton.setPosition(1600, 800);
	eraseButton.setColour(Color::Blue);
	eraseButton.setString("Quit", font, 100, Color::White);

	scene1.addGameObject(playButton);
	scene1.addGameObject(eraseButton);
	scene1.addGameObject(quitButton);

	Menu menu;

	Scene scene2("scene02");



	SpriteObject sprite2("soldierSprite", "head_hurt.png");
	sprite2.setPosition(sf::Vector2f(70.0f, 70.0f));
	sprite2.setScale(sf::Vector2f(5.0f, 5.0f));
	scene2.addGameObject(sprite2);

	SceneHandler handler;
	handler.addScene(scene1);
	handler.addScene(scene2);

	int counter = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::A) {
					if (counter == 0) {
						handler.stackScene("scene02");
						counter++;
					}
					else {
						handler.popScene();
						counter--;
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





