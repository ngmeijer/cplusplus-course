#include <SFML/graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/CharScene.hpp"
#include "../Headers/Arena.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Character.hpp"

#include "../Headers/main.h"

Font font;

int counter = 0;
int* counterPtr = &counter;

void nextScene() {
	counter++;
}

void backToMenu() {
	counter = 0;
}

int main() {
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	Menu menu("menu", window, font);
	CharScene characterGen("character", window, font);
	Arena arena("arena", window, font);

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
					characterGen.checkInput(event, window, mousePosition, handler, counter);
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