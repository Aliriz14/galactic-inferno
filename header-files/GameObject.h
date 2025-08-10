#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void update(sf::Time& dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};