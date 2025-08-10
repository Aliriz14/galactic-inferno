#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <random> // For static random number generation

class Bomb : public GameObject
{
public:
    Bomb(float start_x, float start_y);
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds();
    static void loadTexture(); // Static function to load both bomb textures
    float getRightBound();

private:
    static sf::Texture bomb_textures[2]; // Array to hold 2 different bomb textures
    float move_speed;
    sf::Sprite bomb_sprite;

    // Static random number generator for choosing bomb type
    static std::random_device rd_type;
    static std::uniform_int_distribution<int> dist_type; // Distribution for 0 or 1
};