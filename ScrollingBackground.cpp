#include "header-files/ScrollingBackground.h"
#include "header-files/Globals.h" // For WIN_WIDTH, WIN_HEIGHT

ScrollingBackground::ScrollingBackground()
{
    if (!bg_texture.loadFromFile("assets/1.png"))
    {
        // Handle error: e.g., std::cerr << "Error loading assets/1.png" << std::endl;
    }

    // Set up the first background sprite
    bg_sprites[0].setTexture(bg_texture);
    bg_sprites[0].setScale(
        static_cast<float>(WIN_WIDTH) / bg_texture.getSize().x,
        static_cast<float>(WIN_HEIGHT) / bg_texture.getSize().y
    );
    bg_sprites[0].setPosition(0.f, 0.f);

    // Set up the second background sprite, positioned immediately after the first
    bg_sprites[1].setTexture(bg_texture);
    bg_sprites[1].setScale(
        static_cast<float>(WIN_WIDTH) / bg_texture.getSize().x,
        static_cast<float>(WIN_HEIGHT) / bg_texture.getSize().y
    );
    bg_sprites[1].setPosition(static_cast<float>(WIN_WIDTH), 0.f);
}

void ScrollingBackground::update(sf::Time& dt)
{
    // Move both background sprites
    bg_sprites[0].move(-move_speed * dt.asSeconds(), 0.f);
    bg_sprites[1].move(-move_speed * dt.asSeconds(), 0.f);

    // If the first sprite moves completely off-screen to the left, reposition it to the right of the second
    if (bg_sprites[0].getPosition().x + bg_sprites[0].getGlobalBounds().width < 0)
    {
        bg_sprites[0].setPosition(bg_sprites[1].getPosition().x + bg_sprites[1].getGlobalBounds().width, 0.f);
    }

    // If the second sprite moves completely off-screen to the left, reposition it to the right of the first
    if (bg_sprites[1].getPosition().x + bg_sprites[1].getGlobalBounds().width < 0)
    {
        bg_sprites[1].setPosition(bg_sprites[0].getPosition().x + bg_sprites[0].getGlobalBounds().width, 0.f);
    }
}

void ScrollingBackground::draw(sf::RenderWindow& window)
{
    window.draw(bg_sprites[0]);
    window.draw(bg_sprites[1]);
}