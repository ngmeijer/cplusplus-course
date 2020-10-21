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
	playButton.setSize(200, 100);
	playButton.setColour(Color::Red);
	playButton.setString("Play", font, 100, Color::Blue);

	scene1.addGameObject(playButton);


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





