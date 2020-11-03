#include <iostream>
#include "../Headers/scene.hpp"

Scene::Scene() {
	std::cout << "using empty constructor";
}

Scene::Scene(std::string identifier) : identifier(identifier) { }

Scene::~Scene() { }

void Scene::addGameObject(GameObject& object) {
	this->listOfGameObjects.push_back(&object);
}

void Scene::addTextObject(sf::Text& text) {
	this->listOfTextObjects.push_back(&text);
}

void Scene::addSpriteObject(SpriteObject& sprite) {
	this->listOfSpriteObjects.push_back(&sprite);
}

void Scene::addRectangleObject(sf::RectangleShape& shape) {
	this->listOfRectangleShapes.push_back(&shape);
}

void Scene::addCircleObject(sf::CircleShape& shape) {
	this->listOfCircleShapes.push_back(&shape);
}

void Scene::update() {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->update();
	}
}

void Scene::render(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->render(window);
	}
	for (unsigned int i = 0; i < this->listOfRectangleShapes.size(); i++) {
		window.draw(*listOfRectangleShapes[i]);
	}
	for (unsigned int i = 0; i < this->listOfCircleShapes.size(); i++) {
		window.draw(*listOfCircleShapes[i]);
	}
	for (unsigned int i = 0; i < this->listOfTextObjects.size(); i++) {
		window.draw(*listOfTextObjects[i]);
	}
	for (unsigned int i = 0; i < this->listOfSpriteObjects.size(); i++) {
		this->listOfSpriteObjects[i]->render(window);
	}
}

std::string Scene::getIdentifier() const {
	return this->identifier;
}