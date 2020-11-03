#include "../Headers/Button.hpp"

typedef void(*eventFunction)();

Button::Button() {}

Button::Button(string identifier) : GameObject(identifier) {
	cout << "Button instance has been constructed." << endl;
}

Button::~Button() { }

Vector2f Button::getSize() {
	FloatRect shape = buttonShape.getLocalBounds();

	int width = shape.width;
	int height = shape.height;

	Vector2f size = Vector2f(width, height);

	return size;
}

void Button::setPosition(sf::Vector2f position) {
	buttonShape.setPosition(position.x, position.y);
	sprite.setPosition(position.x, position.y);
}

void Button::setSize(sf::Vector2f size) {
	buttonShape.setSize(Vector2f(size.x, size.y));
}

void Button::setString(string text, const Font& font, int fontSize, Color colour) {
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setCharacterSize(fontSize);
	buttonText.setFillColor(colour);
	buttonText.setPosition((buttonShape.getPosition().x + 20), (buttonShape.getPosition().y));
}

void Button::setSprite(std::string spriteFileName, Vector2f size) {
	this->texture.loadFromFile(spriteFileName);
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(size);
}

void Button::setColour(Color buttonColour) {
	buttonShape.setFillColor(buttonColour);
}

void Button::render(RenderWindow& window) {
	window.draw(this->buttonShape);
	window.draw(this->buttonText);
	window.draw(this->sprite);
}

void Button::update() { }

bool Button::onClick(Vector2f mousePosition) {
	FloatRect buttonBorders = buttonShape.getGlobalBounds();
	float buttonRight = (buttonBorders.left + buttonBorders.width);
	float buttonBottom = (buttonBorders.top + buttonBorders.height);

	if ((mousePosition.x > buttonBorders.left) && (mousePosition.x < buttonRight)) {
		if ((mousePosition.y > buttonBorders.top) && (mousePosition.y < buttonBottom)) {
			return true;
		}
		else return false;
	}
}