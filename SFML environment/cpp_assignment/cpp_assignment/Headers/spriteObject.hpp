#pragma once

#include "../Headers/gameObject.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteObject : public GameObject {
private:
	std::string spriteFile;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	SpriteObject();
	SpriteObject(std::string identifier, std::string spriteFile);
	SpriteObject(const SpriteObject& other);
	~SpriteObject();

public:
	void update() override;
	void render(sf::RenderWindow& window) override;

	void setPosition(sf::Vector2f position);
	void setScale(sf::Vector2f scale);
	void setSprite(std::string spriteName);
	std::string getSpriteFile() const;
};