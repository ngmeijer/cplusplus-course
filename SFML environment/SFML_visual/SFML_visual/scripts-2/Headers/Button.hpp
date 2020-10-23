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
	Font font;

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
	void setString(string text, const Font& font, int fontSize, Color colour);
	void onClick(Vector2f mousePosition);
};