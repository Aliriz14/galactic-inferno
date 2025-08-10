#include "header-files/Meteor.h"
#include "header-files/Globals.h" // For SCALE_FACTOR, WIN_WIDTH, WIN_HEIGHT

// Initialize static members
sf::Texture Meteor::meteor_textures[4]; // Define the static array
float Meteor::move_speed = 250.f; // Adjust speed as needed

// Initialize static random number generator and distribution
std::random_device Meteor::rd_type; // Renamed
std::uniform_int_distribution<int> Meteor::dist_type{ 0, 3 }; // For 4 types (indices 0, 1, 2, 3)

void Meteor::loadTexture()
{
    // Load all four meteor textures
    if (!meteor_textures[0].loadFromFile("assets/meteor1.png")) { /* Handle error */ }
    if (!meteor_textures[1].loadFromFile("assets/meteor2.png")) { /* Handle error */ }
    if (!meteor_textures[2].loadFromFile("assets/meteor3.png")) { /* Handle error */ }
    if (!meteor_textures[3].loadFromFile("assets/meteor4.png")) { /* Handle error */ }
}

Meteor::Meteor(float x_pos, float y_pos)
{
    // Randomly select one of the four textures
    meteor_sprite.setTexture(meteor_textures[dist_type(rd_type)]); // Use rd_type

    // Make the meteor even smaller (adjusted scale for visual size)
    meteor_sprite.setScale(SCALE_FACTOR * 0.25f, SCALE_FACTOR * 0.25f);
    meteor_sprite.setPosition(x_pos, y_pos);
    // Set origin to center for proper collision detection/future rotation if needed
    sf::Vector2u size = meteor_sprite.getTexture()->getSize(); // Get size from the assigned texture
    meteor_sprite.setOrigin(static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f);
}

void Meteor::update(sf::Time& dt)
{
    // Meteors move horizontally from right to left
    meteor_sprite.move(-move_speed * dt.asSeconds(), 0.f);
}

void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(meteor_sprite);
}

sf::FloatRect Meteor::getGlobalBounds()
{
    sf::FloatRect bounds = meteor_sprite.getGlobalBounds();
    // Shrink the collision box slightly (e.g., by 15% from each side)
    // This makes collisions more forgiving and visually accurate.
    float shrink_amount_x = bounds.width * 0.15f;
    float shrink_amount_y = bounds.height * 0.15f;

    bounds.left += shrink_amount_x;
    bounds.top += shrink_amount_y;
    bounds.width -= (2 * shrink_amount_x);
    bounds.height -= (2 * shrink_amount_y);

    return bounds;
}

float Meteor::getRightBound()
{
    return meteor_sprite.getGlobalBounds().left + meteor_sprite.getGlobalBounds().width;
}