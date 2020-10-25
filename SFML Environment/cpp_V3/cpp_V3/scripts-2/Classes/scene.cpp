#include "../Headers/scene.hpp"

Scene::Scene() {}
Scene::Scene(std::string identifier) : identifier(identifier) { }

Scene::~Scene() { }

void Scene::addGameObject(GameObject& object) {
	this->listOfGameObjects.push_back(&object);
}

void Scene::addTextObject(sf::Text& text) {
	this->listOfTextObjects.push_back(&text);
}

void Scene::update() {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->update();
	}
	/*for (unsigned int i = 0; i < this->listOfTextObjects.size(); i++) {
		this->listOfTextObjects[i]->;
	}*/
}

void Scene::render(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->render(window);
	}

	for (unsigned int i = 0; i < this->listOfTextObjects.size(); i++) {
		
	}
}

std::string Scene::getIdentifier() const {
	return this->identifier;
}
