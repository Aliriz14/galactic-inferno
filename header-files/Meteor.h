#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <random> // Include for random number generation

class Meteor : public GameObject
{
public:
    Meteor(float x_pos, float y_pos);
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    static void loadTexture(); // Static function to load all textures

    sf::FloatRect getGlobalBounds(); // This will now return a slightly shrunken box
    float getRightBound(); // For checking if it's off-screen

private:
    static sf::Texture meteor_textures[4]; // Array to hold 4 different meteor textures
    static float move_speed; // Static move speed for all meteors
    sf::Sprite meteor_sprite;

    // Static random number generator and distribution for choosing meteor type
    static std::random_device rd_type; // Renamed to avoid conflict with Game's rd
    static std::uniform_int_distribution<int> dist_type; // Distribution for 0 to 3 (for 4 types)
};