#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/gameObject.hpp"

using namespace std;
using namespace sf;

class Button : public GameObject
{
	typedef void(*eventFunction)();

private:
	RectangleShape buttonShape;
	Text buttonText;
	Font font;
	Sprite sprite;
	Texture texture;

public:
	Button();
	Button(string identifier);
	Button(eventFunction funcPtr);
	~Button();

public:
	void render(sf::RenderWindow& window) override;
	void update() override;

	void operator() () const {
		(m_funcPtr)();
	}

	Vector2f getSize();

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setColour(Color buttonColour);
	void setString(string text, const Font& font, int fontSize, Color colour);
	void setSprite(std::string spriteFileName, sf::Vector2f size);
	bool onClick(Vector2f mousePosition);

private:
	eventFunction m_funcPtr;
};