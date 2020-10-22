#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
    private: 
        const std::string identifier;
    public:
        GameObject(std::string identifier);
        GameObject(const GameObject& other);

        virtual ~GameObject();
    public:
        virtual void update() = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        std::string getIdentifier() const;
};