#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Headers/gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include "../Headers/spriteObject.hpp"

class Scene {
private:
	const std::string identifier;
	std::vector<GameObject*> listOfGameObjects;
	std::vector<sf::Text*> listOfTextObjects;
	std::vector<SpriteObject*> listOfSpriteObjects;
	std::vector<sf::RectangleShape*> listOfRectangleShapes;
	std::vector<sf::CircleShape*> listOfCircleShapes;

public:
	Scene();
	Scene(std::string identifier);
	~Scene();

public:
	void addGameObject(GameObject& object);
	void addTextObject(sf::Text& text);
	void addSpriteObject(SpriteObject& sprite);
	void addRectangleObject(sf::RectangleShape& shape);
	void addCircleObject(sf::CircleShape& shape);

	void removeGameObject(GameObject& object);

	void update();
	void render(sf::RenderWindow& window);
	std::string getIdentifier() const;
};

