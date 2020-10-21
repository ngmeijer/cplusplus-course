#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/gameObject.hpp"

using namespace std;
using namespace sf;

class Button : public GameObject
{
private:
	RectangleShape buttonShape;
	Text buttonText;

public:
	Button();
	Button(string identifier);
	~Button();

public:
	void render(sf::RenderWindow& window) override;
	void update() override;

	void setPosition(int xPos, int yPos);
	void setSize(int width, int height);
	void setColour(Color buttonColour);
	void setString(string text, Font font, int fontSize, Color colour);
};