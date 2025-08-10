#include "header-files/Helicopter.h"
#include "header-files/Globals.h"

Helicopter::Helicopter() :
    velocity_y(0.f),
    velocity_x(0.f), // Initialize horizontal velocity
    move_speed(250.f),    // Combined speed for all directions
    anim_counter(0),
    texture_switch(1),
    should_fly(false)
{
    // Loading the correct helicopter sprites
    textures[0].loadFromFile("assets/helicopter_1.png");
    textures[1].loadFromFile("assets/helicopter_3.png");
    helicopter_sprite.setTexture(textures[0]);
    helicopter_sprite.setScale(SCALE_FACTOR * 0.20f, SCALE_FACTOR * 0.20f);

    sf::Vector2u texture_size = textures[0].getSize();
    helicopter_sprite.setOrigin(static_cast<float>(texture_size.x) / 2.f, static_cast<float>(texture_size.y) / 2.f);

    resetHelicopterPosition();
}

void Helicopter::update(sf::Time& dt)
{
    if (should_fly)
    {
        // Apply both horizontal and vertical velocity
        helicopter_sprite.move(velocity_x * dt.asSeconds(), velocity_y * dt.asSeconds());

        // Boundary checks for all four directions
        // Left boundary
        if (helicopter_sprite.getPosition().x - helicopter_sprite.getGlobalBounds().width / 2.f < 0.f)
        {
            helicopter_sprite.setPosition(helicopter_sprite.getGlobalBounds().width / 2.f, helicopter_sprite.getPosition().y);
            velocity_x = 0.f;
        }
        // Right boundary
        if (helicopter_sprite.getPosition().x + helicopter_sprite.getGlobalBounds().width / 2.f > WIN_WIDTH)
        {
            helicopter_sprite.setPosition(WIN_WIDTH - helicopter_sprite.getGlobalBounds().width / 2.f, helicopter_sprite.getPosition().y);
            velocity_x = 0.f;
        }
        // Top boundary
        if (helicopter_sprite.getPosition().y - helicopter_sprite.getGlobalBounds().height / 2.f < 0.f)
        {
            helicopter_sprite.setPosition(helicopter_sprite.getPosition().x, helicopter_sprite.getGlobalBounds().height / 2.f);
            velocity_y = 0.f;
        }
        // Bottom boundary
        if (helicopter_sprite.getPosition().y + helicopter_sprite.getGlobalBounds().height / 2.f > WIN_HEIGHT)
        {
            helicopter_sprite.setPosition(helicopter_sprite.getPosition().x, WIN_HEIGHT - helicopter_sprite.getGlobalBounds().height / 2.f);
            velocity_y = 0.f;
        }

        // Basic animation for the helicopter
        if (anim_counter == 5)
        {
            helicopter_sprite.setTexture(textures[texture_switch]);
            if (texture_switch) texture_switch = 0;
            else texture_switch = 1;
            anim_counter = 0;
        }
        anim_counter++;
    }
}

void Helicopter::draw(sf::RenderWindow& window)
{
    window.draw(helicopter_sprite);
}

// Control methods for horizontal movement
void Helicopter::moveHelicopterUp()
{
    velocity_y = -move_speed;
}

void Helicopter::moveHelicopterDown()
{
    velocity_y = move_speed;
}

void Helicopter::stopVerticalMovement()
{
    velocity_y = 0.f;
}

void Helicopter::moveHelicopterLeft()
{
    velocity_x = -move_speed;
}

void Helicopter::moveHelicopterRight()
{
    velocity_x = move_speed;
}

void Helicopter::stopHorizontalMovement()
{
    velocity_x = 0.f;
}

float Helicopter::getRightBound()
{
    return helicopter_sprite.getGlobalBounds().left + helicopter_sprite.getGlobalBounds().width;
}

sf::FloatRect Helicopter::getGlobalBounds()
{
    sf::FloatRect bounds = helicopter_sprite.getGlobalBounds();
    float shrink_amount_x = bounds.width * 0.15f;
    float shrink_amount_y = bounds.height * 0.15f;

    bounds.left += shrink_amount_x;
    bounds.top += shrink_amount_y;
    bounds.width -= (2 * shrink_amount_x);
    bounds.height -= (2 * shrink_amount_y);

    return bounds;
}

void Helicopter::resetHelicopterPosition()
{
    helicopter_sprite.setPosition(WIN_WIDTH / 4.f, WIN_HEIGHT / 2.f);
    velocity_y = 0.f;
    velocity_x = 0.f;
    should_fly = false;
    helicopter_sprite.setRotation(0.f);
}

void Helicopter::setShouldFly(bool fly)
{
    should_fly = fly;
}