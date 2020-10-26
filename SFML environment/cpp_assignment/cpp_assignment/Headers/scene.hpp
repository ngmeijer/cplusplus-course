#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Headers/gameObject.hpp"
#include <SFML/Graphics/Text.hpp>

class Scene {
private:
	const std::string identifier;
	std::vector<GameObject*> listOfGameObjects;
	std::vector<sf::Text*> listOfTextObjects;

public:
	Scene();
	Scene(std::string identifier);
	~Scene();

public:
	void addGameObject(GameObject& object);
	void addTextObject(sf::Text& text);
	void update();
	void render(sf::RenderWindow& window);
	std::string getIdentifier() const;
};

