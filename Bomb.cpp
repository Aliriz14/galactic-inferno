#include "header-files/Bomb.h"
#include "header-files/Globals.h" // For SCALE_FACTOR

// Initialize static members
sf::Texture Bomb::bomb_textures[2];
std::random_device Bomb::rd_type;
std::uniform_int_distribution<int> Bomb::dist_type{ 0, 1 };

void Bomb::loadTexture()
{
    if (!bomb_textures[0].loadFromFile("assets/b1.png"))
    {
        // Handle error: e.g., std::cerr << "Error loading assets/b1.png" << std::endl;
    }
    if (!bomb_textures[1].loadFromFile("assets/b2.png"))
    {
        // Handle error: e.g., std::cerr << "Error loading assets/b2.png" << std::endl;
    }
}

Bomb::Bomb(float start_x, float start_y) : move_speed(350.f) // Adjust bomb speed as needed
{
    // Randomly select one of the two bomb textures
    bomb_sprite.setTexture(bomb_textures[dist_type(rd_type)]);

    // Set a very small scale for the bombs
    bomb_sprite.setScale(SCALE_FACTOR * 0.1f, SCALE_FACTOR * 0.1f); // Adjust size as needed

    // Set origin to center for proper positioning/rotation if needed later
    sf::Vector2u size = bomb_sprite.getTexture()->getSize();
    bomb_sprite.setOrigin(static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f);

    bomb_sprite.setPosition(start_x, start_y);
}

void Bomb::update(sf::Time& dt)
{
    // Bombs move horizontally from right to left
    bomb_sprite.move(-move_speed * dt.asSeconds(), 0.f);
}

void Bomb::draw(sf::RenderWindow& window)
{
    window.draw(bomb_sprite);
}

sf::FloatRect Bomb::getGlobalBounds()
{
    sf::FloatRect bounds = bomb_sprite.getGlobalBounds();
    // You can shrink the collision box if the sprite has a lot of transparent space
    // float shrink_amount_x = bounds.width * 0.1f;
    // float shrink_amount_y = bounds.height * 0.1f;
    // bounds.left += shrink_amount_x;
    // bounds.top += shrink_amount_y;
    // bounds.width -= (2 * shrink_amount_x);
    // bounds.height -= (2 * shrink_amount_y);
    return bounds;
}

float Bomb::getRightBound()
{
    return bomb_sprite.getGlobalBounds().left + bomb_sprite.getGlobalBounds().width;
}