#include "header-files/Pipe.h"
#include "header-files/Globals.h"

sf::Texture Pipe::pipe_texture; // This line is the one and only declaration of the static texture.
int Pipe::move_speed = 400;

void Pipe::loadTexture()
{
    if (!pipe_texture.loadFromFile("assets/pipe.png"))
    {
        // Handle error if texture not found
    }
}

Pipe::Pipe(int x_pos, int y_pos)
{
    pipe_sprite.setTexture(pipe_texture);
    pipe_sprite.setScale(SCALE_FACTOR * 0.7f, SCALE_FACTOR * 0.7f);
    pipe_sprite.setPosition(static_cast<float>(x_pos), static_cast<float>(y_pos));
}

void Pipe::update(sf::Time& dt)
{
    pipe_sprite.move(-move_speed * dt.asSeconds(), 0.f);
}

void Pipe::draw(sf::RenderWindow& window)
{
    window.draw(pipe_sprite);
}

float Pipe::getRightBound()
{
    return pipe_sprite.getGlobalBounds().left + pipe_sprite.getGlobalBounds().width;
}

sf::FloatRect Pipe::getGlobalBounds()
{
    return pipe_sprite.getGlobalBounds();
}