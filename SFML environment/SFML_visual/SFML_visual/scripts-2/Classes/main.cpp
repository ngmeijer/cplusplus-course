#include <SFML/Graphics.hpp>

#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"

Font font;

Text menuText[3];

int yPosText = 65;
int xPosText = 1620;

void draw(RenderWindow& window) {
	for (int i = 0; i < maxText; i++) {
		window.draw(menuText[i]);
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	/*for (int index = 0; index < maxText; index++)
	{
		menuText[index].setFont(font);
		menuText[index].setCharacterSize(50);
		menuText[index].setOutlineColor(Color::White);
		yPosText += 250;
		menuText[index].setPosition(xPosText, yPosText);
		menuText[index].setOrigin(menuText[index].getLocalBounds().width / 2, menuText[index].getLocalBounds().height / 2);
	}*/

	menuText[1].setString("Erase Data");
	menuText[2].setString("Quit");

	Scene scene1("menu");

	Button playButton;
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


	scene1.addGameObject(playButton);
	scene1.addGameObject(eraseButton);
	scene1.addGameObject(quitButton);

	Menu menu;
	scene1.addGameObject(menu);


	Scene scene2("scene02");
	

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
		float mousePositionX = Mouse::getPosition(window).x;
		float mousePositionY = Mouse::getPosition(window).y;
		Vector2f mousePosition = Vector2f(mousePositionX, mousePositionY);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left) {
				playButton.onClick(mousePosition);
			}
		}

		window.clear();
		handler.update();
		handler.render(window);
		draw(window);
		window.display();
	}

	return 0;
}





