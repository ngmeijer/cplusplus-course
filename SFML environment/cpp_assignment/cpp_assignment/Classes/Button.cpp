#include "../Headers/Button.hpp"

typedef void(*eventFunction)();

Button::Button() {}

Button::Button(std::string identifier) : GameObject(identifier) {
	std::cout << "Button instance has been constructed." << std::endl;
}

Button::~Button() { }

sf::Vector2f Button::getSize() {
	sf::FloatRect shape = buttonShape.getLocalBounds();

	int width = shape.width;
	int height = shape.height;

	sf::Vector2f size = sf::Vector2f(width, height);

	return size;
}

void Button::setPosition(sf::Vector2f position) {
	buttonShape.setPosition(position.x, position.y);
	sprite.setPosition(position.x, position.y);
}

void Button::setSize(sf::Vector2f size) {
	buttonShape.setSize(sf::Vector2f(size.x, size.y));
}

void Button::setString(std::string text, const sf::Font& font, int fontSize, sf::Color colour) {
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setCharacterSize(fontSize);
	buttonText.setFillColor(colour);
	buttonText.setPosition((buttonShape.getPosition().x + 20), (buttonShape.getPosition().y));
}

void Button::setSprite(std::string spriteFileName, sf::Vector2f size) {
	this->texture.loadFromFile(spriteFileName);
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(size);
}

void Button::setColour(sf::Color buttonColour) {
	buttonShape.setFillColor(buttonColour);
}

void Button::render(sf::RenderWindow& window) {
	window.draw(this->buttonShape);
	window.draw(this->buttonText);
	window.draw(this->sprite);
}

void Button::update() { }

bool Button::onClick(sf::Vector2f mousePosition) {
	sf::FloatRect buttonBorders = buttonShape.getGlobalBounds();
	float buttonRight = (buttonBorders.left + buttonBorders.width);
	float buttonBottom = (buttonBorders.top + buttonBorders.height);

	if ((mousePosition.x > buttonBorders.left) && (mousePosition.x < buttonRight)) {
		if ((mousePosition.y > buttonBorders.top) && (mousePosition.y < buttonBottom)) {
			return true;
		}
		else return false;
	}
}