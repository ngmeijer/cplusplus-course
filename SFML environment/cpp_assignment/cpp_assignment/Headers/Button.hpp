#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/gameObject.hpp"

class Button : public GameObject
{
private:
	sf::RectangleShape buttonShape;
	sf::Text buttonText;
	sf::Font font;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Button();
	Button(std::string identifier);
	~Button();

public:
	void render(sf::RenderWindow& window) override;
	void update() override;

	sf::Vector2f getSize();

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setColour(sf::Color buttonColour);
	void setString(std::string text, const sf::Font& font, int fontSize, sf::Color colour);
	void setSprite(std::string spriteFileName, sf::Vector2f size);
	bool onClick(sf::Vector2f mousePosition);

private:

};