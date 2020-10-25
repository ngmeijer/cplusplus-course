#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"

using namespace sf;

const int maxText = 3;


class Menu
{
public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void draw(RenderWindow& window);
	void defineButtons();
	void checkInput(RenderWindow& window);

private:
	Font font;
	Text menuText[maxText];
};

