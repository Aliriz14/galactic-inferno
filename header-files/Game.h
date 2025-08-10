#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include "Helicopter.h"
#include "Missile.h"
#include "Meteor.h"
#include "ScrollingBackground.h"
#include "Explosion.h"
#include "Projectile.h"
#include "Bomb.h"
#include "Globals.h"
#include <string>

enum GameState {
    MainMenu,
    InGame,
    Exploding,
    GameOver,
    Scores,
    Instructions
};

class Game
{
public:
    Game(sf::RenderWindow&);
    sf::RenderWindow& win;
    void startGameLoop();

private:
    ScrollingBackground scrolling_background;

    Helicopter helicopter;
    std::vector<Missile> missiles;
    std::vector<Meteor> meteors;
    std::vector<Bomb> bombs;
    std::vector<Explosion> explosions;
    std::vector<Projectile> projectiles;
    bool helicopter_visible;

    GameState current_state;
    int missile_counter;
    int missile_spawn_time;
    int meteor_counter;
    int meteor_spawn_time;
    int bomb_counter;
    int bomb_spawn_time;
    int score;
    sf::Clock score_timer;
    sf::Clock explosion_timer;
    const float EXPLOSION_DURATION = 0.8f;

    sf::Clock projectile_fire_rate_timer;
    const float PROJECTILE_FIRE_RATE = 0.2f;

    std::random_device rd;
    std::uniform_int_distribution<int> missile_y_dist{ 50, WIN_HEIGHT - 50 };
    std::uniform_int_distribution<int> missile_burst_dist{ 1, 1 };
    std::uniform_real_distribution<float> missile_rotation_dist{ -95.f, -85.f };

    std::uniform_int_distribution<int> meteor_y_dist{ 100, WIN_HEIGHT - 100 };
    std::uniform_int_distribution<int> meteor_burst_dist{ 1, 3 };
    std::uniform_int_distribution<int> meteor_x_spawn_offset_dist{ 0, 150 };

    std::uniform_int_distribution<int> bomb_y_dist{ 100, WIN_HEIGHT - 100 };
    std::uniform_int_distribution<int> bomb_burst_dist{ 1, 3 };
    std::uniform_int_distribution<int> bomb_x_spawn_offset_dist{ 0, 100 };

    std::uniform_int_distribution<int> explosion_type_dist{ 0, 1 };

    sf::Font font;
    sf::Text restart_text;
    sf::Text score_text;

    sf::Texture start_button_texture;
    sf::Sprite start_button_sprite;
    sf::Texture scores_button_texture;
    sf::Sprite scores_button_sprite;
    sf::Texture exit_button_texture;
    sf::Sprite exit_button_sprite;

    sf::Texture you_lose_texture;
    sf::Sprite you_lose_sprite;

    sf::Text back_button;
    sf::Text high_scores_text;

    // NEW: Members for Instructions screen
    sf::Texture info_button_texture;
    sf::Sprite info_button_sprite;
    sf::Texture instructions_window_texture;
    sf::Sprite instructions_window_sprite;
    sf::Text instructions_text;
    sf::Text close_button_text;

    // NEW: Members for Sound button
    sf::Texture sound_button_texture;
    sf::Sprite sound_button_sprite;
    bool is_muted = false;

    std::vector<int> high_scores;
    const std::string scores_filename = "scores.txt";

    sf::SoundBuffer flap_buffer, dead_buffer;
    sf::Sound flap_sound, dead_sound;
    sf::SoundBuffer shoot_buffer;
    sf::Sound shoot_sound;
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;

    sf::Music background_music;

    void draw();
    void doProcessing(sf::Time& dt);
    void checkCollisions();
    void restartGame();
    std::string toString(int);

    void drawMainMenu();
    void handleMainMenuEvents(sf::Event& event);
    void drawGameOver();
    void handleGameOverEvents(sf::Event& event);
    void drawScores();
    void handleScoresEvents(sf::Event& event);
    void saveScore();
    void loadScores();

    // NEW: Methods for the new features
    void drawInstructions();
    void handleInstructionsEvents(sf::Event& event);
    void toggleMute();
};