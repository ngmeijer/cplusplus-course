#include <SFML/graphics.hpp>

#include "../Headers/scene.hpp"
#include "../Headers/menu.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"
#include "../Headers/Button.hpp"

Font font;

Text menuText[3];

vector<int> randomHealth = { 50, 75, 60 };
vector<int> randomCharacterValues = {};

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
	cout << "execution";
	counter = 0;
}

void generateCharacter() {
	m_strength = rand();
	cout << m_strength;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arena game!");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("font.ttf")) {
		cout << "Missing font." << endl;
	}

	//generateCharacter();

	Scene menu("menu");
	Scene character("character");
	Scene fight("fight");

	Text title;
	title.setFont(font);
	title.setCharacterSize(80);
	title.setPosition((window.getSize().x / 2 - 250), 50);
	title.setString("Nether Fights");

	SpriteObject background("background", "titleBG.jpg");
	background.setPosition(sf::Vector2f(400, 200));
	background.setScale(sf::Vector2f(0.6f, 0.6f));

	Button playButton(&nextScene);
	playButton.setSize(250, 100);
	playButton.setPosition(1600, 300);
	playButton.setColour(Color::Red);
	playButton.setString("Play", font, 100, Color::White);

	Button eraseButton;
	eraseButton.setSize(250, 100);
	eraseButton.setPosition(1600, 550);
	eraseButton.setColour(Color::Magenta);
	eraseButton.setString("Erase data", font, 50, Color::White);

	Button quitButton;
	quitButton.setSize(250, 100);
	quitButton.setPosition(1600, 800);
	quitButton.setColour(Color::Blue);
	quitButton.setString("Quit", font, 100, Color::White);

	menu.addGameObject(playButton);
	menu.addGameObject(eraseButton);
	menu.addGameObject(quitButton);
	menu.addTextObject(title);
	menu.addGameObject(background);

	//Menu menu;
	//scene1.addGameObject(menu);

	Button generateButton;
	generateButton.setSize(400, 150);
	generateButton.setPosition((window.getSize().x / 2 - generateButton.getSize().x / 2), (window.getSize().y - generateButton.getSize().y - 50));
	generateButton.setColour(Color::Magenta);
	generateButton.setString("Generate", font, 100, Color::White);

	Button cancelButton(&backToMenu);
	cancelButton.setSize(200, 100);
	cancelButton.setPosition(1650, 950);
	cancelButton.setColour(Color::White);
	cancelButton.setString("Cancel", font, 50, Color::Black);

	Text strength;
	strength.setFont(font);
	strength.setCharacterSize(80);
	strength.setPosition(300, 300);
	strength.setString("Strength: ");

	Text agility;
	agility.setFont(font);
	agility.setCharacterSize(80);
	agility.setPosition(850, 300);
	agility.setString("Agility: ");

	Text wits;
	wits.setFont(font);
	wits.setCharacterSize(80);
	wits.setPosition(1400, 300);
	wits.setString(("Wits:\n"));

	character.addGameObject(generateButton);
	character.addGameObject(cancelButton);
	character.addTextObject(strength);
	character.addTextObject(agility);
	character.addTextObject(wits);

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

			if (event.type == sf::Event::MouseButtonPressed) {
				float mousePositionX = Mouse::getPosition(window).x;
				float mousePositionY = Mouse::getPosition(window).y;
				Vector2f mousePosition = Vector2f(mousePositionX, mousePositionY);

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (playButton.onClick(mousePosition) == true && counter == 0)
					{
						if (counter == 0) {
							handler.stackScene("character");
							counter++;
						}
						else {
							handler.popScene();
							counter--;
						}
					}

					if (quitButton.onClick(mousePosition) == true && counter == 0) {
						window.close();
					}

					if (cancelButton.onClick(mousePosition) == true && counter == 1) {
						if (counter == 1) {
							handler.stackScene("menu");
							counter--;
						}
						else {
							handler.popScene();
							counter++;
						}
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





