#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class ScrollingBackground : public GameObject
{
private:
    sf::Texture bg_texture;
    sf::Sprite bg_sprites[2]; // Two sprites for seamless scrolling
    const float move_speed = 100.f; // Adjust speed as needed

public:
    ScrollingBackground();
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
};