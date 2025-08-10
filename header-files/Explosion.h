 #pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random> // Added for static random device in .cpp

class Explosion
{
public:
    Explosion(sf::Vector2f position, int type); // Added 'type' parameter
    void update(sf::Time& dt);
    void draw(sf::RenderWindow& window);
    bool isFinished() const; // To check if the animation is done

    static void loadTextures(); // Static function to load all explosion textures

private:
    static sf::Texture explosion_textures_type1[9]; // Array for 9 frames of type 1
    static sf::Texture explosion_textures_type2[9]; // Array for 9 frames of type 2

    sf::Sprite sprite;
    int current_frame;
    sf::Clock frame_timer;
    float frame_duration; // How long each frame is displayed
    bool finished;

    int explosion_type; // Store which type of explosion this object is
};