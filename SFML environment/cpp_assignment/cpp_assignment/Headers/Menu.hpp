#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/spriteObject.hpp"
#include "../Headers/sceneHandler.hpp"

using namespace sf;

const int maxText = 3;

class Menu : public Scene
{
public:
	Menu();
	Menu(float width, float height, RenderWindow& windowRef, Font& font);
	~Menu();

	void handleText(RenderWindow& window);
	void handleBackground();
	void handleButtons();
	void defineButtons();
	void checkInput(Event event, RenderWindow& window, Vector2f mousePos, SceneHandler handler, int counter);

private:

};