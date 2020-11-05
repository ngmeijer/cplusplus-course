#include "../Headers/spriteObject.hpp"

SpriteObject::SpriteObject() { }

SpriteObject::SpriteObject(std::string identifier, std::string spriteFile) :
	GameObject(identifier), spriteFile(spriteFile)
{
	this->texture.loadFromFile(this->spriteFile);
	this->sprite.setTexture(this->texture);
}

SpriteObject::SpriteObject(const SpriteObject& other) :
	GameObject(other.getIdentifier()), spriteFile(other.getSpriteFile())
{
	this->texture.loadFromFile(this->spriteFile);
	this->sprite.setTexture(this->texture);
}

SpriteObject::~SpriteObject() { }

void SpriteObject::update() {

}

void SpriteObject::render(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

void SpriteObject::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
}

void SpriteObject::setScale(sf::Vector2f scale) {
	sprite.setScale(scale);
}

void SpriteObject::setSprite(std::string spriteName)
{
	this->texture.loadFromFile(spriteName);
	this->sprite.setTexture(this->texture);
}

std::string SpriteObject::getSpriteFile() const {
	return this->spriteFile;
}