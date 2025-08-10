#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <random> // Include for random number generation

class Missile : public GameObject
{
public:
    Missile(float start_x, float start_y, float initial_rotation); // Added initial_rotation parameter
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds();
    static void loadTexture(); // Static function to load all textures
    float getRightBound();

private:
    static sf::Texture missile_textures[2]; // Array to hold 2 different missile textures
    float move_speed;
    sf::Sprite missile_sprite;

    // Static random number generator for choosing missile type
    static std::random_device rd_type; // Renamed to avoid conflict with Game's rd
    static std::uniform_int_distribution<int> dist_type; // Distribution for 0 to 1 (for 2 types)
};