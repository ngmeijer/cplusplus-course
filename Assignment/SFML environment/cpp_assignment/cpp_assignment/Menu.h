#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

const int maxText = 2;


class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(RenderWindow& window);
	void defineButtons();
	void calculateButtonBorders(int index, int left, int top, int right, int bottom, int width, int height);
	void checkInput(RenderWindow& window);

private:
	Font font;
	Text menuText[maxText];
};

