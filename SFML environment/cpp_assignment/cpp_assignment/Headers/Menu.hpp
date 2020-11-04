#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"

using namespace sf;

class Menu : public Scene
{
private:
	sf::Font m_font;

public:
	Menu();
	Menu(std::string identifier, RenderWindow& windowRef, Font& font);
	~Menu();

	void handleText();
	void handleBackground();
	void handleButtons();
	void checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler& handler, int& counter);

private:

};