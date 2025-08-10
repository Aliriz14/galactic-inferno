#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Pipe : public GameObject
{
public:
    Pipe(int x_pos, int y_pos);
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    static void loadTexture();

    float getRightBound();
    sf::FloatRect getGlobalBounds();

    bool hasScored() const { return scored; }
    void setScored(bool s) { scored = s; }

private:
    static sf::Texture pipe_texture;
    static int move_speed;
    sf::Sprite pipe_sprite;
    bool scored = false;
};