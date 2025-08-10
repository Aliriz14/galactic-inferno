#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Projectile : public GameObject
{
public:
    Projectile(float start_x, float start_y);
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds();
    static void loadTexture(); // Static function to load the projectile texture once
    float getLeftBound(); // To check if it's off-screen to the right

private:
    static sf::Texture projectile_texture; // Static texture for all projectiles
    float move_speed;
    sf::Sprite projectile_sprite;
};