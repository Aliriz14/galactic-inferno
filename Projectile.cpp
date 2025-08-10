#include "header-files/Projectile.h"
#include "header-files/Globals.h" // For SCALE_FACTOR

// Initialize static members
sf::Texture Projectile::projectile_texture;

void Projectile::loadTexture()
{
    if (!projectile_texture.loadFromFile("assets/projectile.png"))
    {
        // Handle error: e.g., std::cerr << "Error loading assets/projectile.png" << std::endl;
    }
}

Projectile::Projectile(float start_x, float start_y) : move_speed(700.f) // Projectile moves faster
{
    projectile_sprite.setTexture(projectile_texture);
    // Scale the projectile to be small but visible
    projectile_sprite.setScale(SCALE_FACTOR * 0.1f, SCALE_FACTOR * 0.1f); // Adjust size as needed
    projectile_sprite.setPosition(start_x, start_y);

    // Set origin to center for consistent positioning/rotation if needed later
    sf::Vector2u size = projectile_texture.getSize();
    projectile_sprite.setOrigin(static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f);
}

void Projectile::update(sf::Time& dt)
{
    // Projectiles move horizontally from left to right
    projectile_sprite.move(move_speed * dt.asSeconds(), 0.f);
}

void Projectile::draw(sf::RenderWindow& window)
{
    window.draw(projectile_sprite);
}

sf::FloatRect Projectile::getGlobalBounds()
{
    sf::FloatRect bounds = projectile_sprite.getGlobalBounds();
    // You can shrink the collision box if the sprite has a lot of transparent space
    // float shrink_amount_x = bounds.width * 0.1f;
    // float shrink_amount_y = bounds.height * 0.1f;
    // bounds.left += shrink_amount_x;
    // bounds.top += shrink_amount_y;
    // bounds.width -= (2 * shrink_amount_x);
    // bounds.height -= (2 * shrink_amount_y);
    return bounds;
}

float Projectile::getLeftBound()
{
    return projectile_sprite.getGlobalBounds().left;
}