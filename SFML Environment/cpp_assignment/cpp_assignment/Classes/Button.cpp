#include "../Headers/Button.hpp"

Button::Button() {}

Button::Button(string identifier) : GameObject(identifier)
{
	cout << "Button instance has been constructed." << endl;
}

Button::~Button() {
	cout << "Button instance has been destroyed." << endl;
};

void Button::setPosition(int xPos, int yPos) {
	buttonShape.setPosition(xPos, yPos);
}

void Button::setSize(int width, int height) {
	buttonShape.setSize(Vector2f(width, height));
}

void Button::setString(string text, Font font, int fontSize, Color colour) {
	buttonText.setString(text);
	buttonText.setFont(font);
}

void Button::setColour(Color buttonColour) {
	buttonShape.setFillColor(buttonColour);
}

void Button::render(RenderWindow& window) {

	window.draw(this->buttonShape);
	//window.draw(this->buttonText);
}

void Button::update() { }

void Button::onClick(Vector2f mousePosition) {
	FloatRect buttonBorders = buttonShape.getGlobalBounds();

	if ((mousePosition.x > buttonBorders.left) && (mousePosition.x < buttonBorders.width)){
		cout << "running";
		cout << "clicked!";
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {
	}
}