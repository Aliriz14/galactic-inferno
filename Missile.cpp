#include "header-files/Missile.h"
#include "header-files/Globals.h"
#include <cmath>

// Initialize static members
sf::Texture Missile::missile_textures[2]; // Define the static array
std::random_device Missile::rd_type; // Initialize static random device
std::uniform_int_distribution<int> Missile::dist_type{ 0, 1 }; // Initialize distribution for 2 types (indices 0, 1)

void Missile::loadTexture()
{
    // Load both missile textures
    if (!missile_textures[0].loadFromFile("assets/missile1.png")) { /* Handle error */ }
    if (!missile_textures[1].loadFromFile("assets/missile2.png")) { /* Handle error */ }
}

Missile::Missile(float start_x, float start_y, float initial_rotation) : move_speed(500.f) // Added initial_rotation parameter
{
    // Randomly select one of the two textures
    missile_sprite.setTexture(missile_textures[dist_type(rd_type)]);

    // Make the missile very small
    missile_sprite.setScale(SCALE_FACTOR * 0.15f, SCALE_FACTOR * 0.15f);
    missile_sprite.setPosition(start_x, start_y);

    // Set the rotation based on the provided parameter
    missile_sprite.setRotation(initial_rotation);

    // Set origin to center for proper rotation
    sf::Vector2u size = missile_sprite.getTexture()->getSize(); // Get size from the assigned texture
    missile_sprite.setOrigin(static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f);
}

void Missile::update(sf::Time& dt)
{
    // Move the missile horizontally towards the left
    missile_sprite.move(-move_speed * dt.asSeconds(), 0.f);
}

void Missile::draw(sf::RenderWindow& window)
{
    window.draw(missile_sprite);
}

sf::FloatRect Missile::getGlobalBounds()
{
    sf::FloatRect bounds = missile_sprite.getGlobalBounds();
    // Shrink the collision box slightly (e.g., by 15% from each side)
    float shrink_amount_x = bounds.width * 0.15f;
    float shrink_amount_y = bounds.height * 0.15f;

    bounds.left += shrink_amount_x;
    bounds.top += shrink_amount_y;
    bounds.width -= (2 * shrink_amount_x);
    bounds.height -= (2 * shrink_amount_y);

    return bounds;
}

float Missile::getRightBound()
{
    return missile_sprite.getGlobalBounds().left + missile_sprite.getGlobalBounds().width;
}