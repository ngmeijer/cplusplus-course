#include "gameObject.hpp"

GameObject::GameObject(std::string identifier) : identifier(identifier) { }
 
GameObject::GameObject(const GameObject& other) : identifier(other.getIdentifier()) { }

GameObject::~GameObject() { }

std::string GameObject::getIdentifier() const {
    return this->identifier;
}