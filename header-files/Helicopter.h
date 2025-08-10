#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Helicopter : public GameObject
{
public:
    Helicopter();
    void update(sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

    // New control methods for continuous horizontal and vertical movement
    void moveHelicopterUp();
    void moveHelicopterDown();
    void stopVerticalMovement();
    void moveHelicopterLeft();
    void moveHelicopterRight();
    void stopHorizontalMovement();

    float getRightBound();
    sf::FloatRect getGlobalBounds();
    void resetHelicopterPosition();
    void setShouldFly(bool should_fly);

private:
    sf::Texture textures[2];
    sf::Sprite helicopter_sprite;
    float velocity_y;
    float velocity_x; // Added for horizontal movement
    float move_speed; // Single variable for both horizontal and vertical speed
    int anim_counter;
    int texture_switch;
    bool should_fly;
};