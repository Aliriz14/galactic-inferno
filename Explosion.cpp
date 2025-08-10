#include "header-files/Explosion.h"
#include "header-files/Globals.h" // For SCALE_FACTOR
#include <iostream> // Added for debugging output

// Initialize static members
sf::Texture Explosion::explosion_textures_type1[9];
sf::Texture Explosion::explosion_textures_type2[9];

void Explosion::loadTextures()
{
    // Load all 9 explosion frames for Type 1
    for (int i = 0; i < 9; ++i)
    {
        // Using a simpler naming convention: explosion1_1.png to explosion1_9.png
        std::string filename = "assets/explosion1_" + std::to_string(i + 1) + ".png";
        if (!explosion_textures_type1[i].loadFromFile(filename))
        {
            std::cerr << "Error loading explosion texture: " << filename << std::endl; // Debugging output
        }
    }

    // Load all 9 explosion frames for Type 2
    for (int i = 0; i < 9; ++i)
    {
        // Using a simpler naming convention: explosion2_1.png to explosion2_9.png
        std::string filename = "assets/explosion2_" + std::to_string(i + 1) + ".png";
        if (!explosion_textures_type2[i].loadFromFile(filename))
        {
            std::cerr << "Error loading explosion texture: " << filename << std::endl; // Debugging output
        }
    }
    std::cout << "Explosion textures load attempt complete." << std::endl; // Debugging output
}

Explosion::Explosion(sf::Vector2f position, int type) :
    current_frame(4), // Start from the fifth frame (index 4)
    frame_duration(0.05f), // Each frame lasts 0.05 seconds (adjust for speed)
    finished(false),
    explosion_type(type) // Store the explosion type
{
    // Set the initial texture based on the explosion type, starting from index 4
    if (explosion_type == 0) {
        sprite.setTexture(explosion_textures_type1[current_frame]);
    }
    else { // explosion_type == 1
        sprite.setTexture(explosion_textures_type2[current_frame]);
    }

    // Reduced scale for a smaller explosion
    sprite.setScale(SCALE_FACTOR * 0.35f, SCALE_FACTOR * 0.35f); // <--- Adjusted this value

    // Set origin to center for proper positioning at collision point
    // This uses the size of the *currently assigned* texture
    sf::Vector2u current_texture_size = sprite.getTexture()->getSize();
    sprite.setOrigin(static_cast<float>(current_texture_size.x) / 2.f,
        static_cast<float>(current_texture_size.y) / 2.f);
    sprite.setPosition(position);
    frame_timer.restart();
    std::cout << "Explosion created at (" << position.x << ", " << position.y << ") Type: " << type << std::endl; // Debugging output
}

void Explosion::update(sf::Time& dt)
{
    if (finished) return;

    if (frame_timer.getElapsedTime().asSeconds() >= frame_duration)
    {
        current_frame++;
        // The animation will now play frames from index 4 up to (but not including) 9.
        // This means indices 4, 5, 6, 7, 8 will be displayed (5 frames total).
        if (current_frame < 9)
        {
            // Update texture based on the stored explosion type
            if (explosion_type == 0) {
                sprite.setTexture(explosion_textures_type1[current_frame]);
            }
            else {
                sprite.setTexture(explosion_textures_type2[current_frame]);
            }
            frame_timer.restart();
            // std::cout << "Explosion frame: " << current_frame << std::endl; // Uncomment for very detailed frame-by-frame debug
        }
        else
        {
            finished = true; // Animation complete
            std::cout << "Explosion animation finished." << std::endl; // Debugging output
        }
    }
}

void Explosion::draw(sf::RenderWindow& window)
{
    if (!finished)
    {
        window.draw(sprite);
    }
}

bool Explosion::isFinished() const
{
    return finished;
}