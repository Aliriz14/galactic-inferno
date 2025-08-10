#include "header-files/Game.h"
#include "header-files/Globals.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>
#include <iostream>

Game::Game(sf::RenderWindow& window) : win(window),
current_state(MainMenu),
missile_counter(0),
missile_spawn_time(75),
meteor_counter(0),
meteor_spawn_time(150),
bomb_counter(0),
bomb_spawn_time(180),
score(0),
helicopter_visible(true)
{
    win.setFramerateLimit(60);

    font.loadFromFile("assets/PressStart2P-Regular.ttf");

    restart_text.setFont(font);
    restart_text.setCharacterSize(48);
    restart_text.setFillColor(sf::Color::Yellow);
    restart_text.setString("Restart Game!!");
    restart_text.setOrigin(restart_text.getGlobalBounds().width / 2.f, restart_text.getGlobalBounds().height / 2.f);
    restart_text.setPosition(WIN_WIDTH / 2.f, 650.f);

    score_text.setFont(font);
    score_text.setCharacterSize(30);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(15.f, 15.f);
    score_text.setString("Score: 0");

    if (!start_button_texture.loadFromFile("assets/start_button.png")) {
        std::cerr << "Error loading start_button.png" << std::endl;
    }
    start_button_sprite.setTexture(start_button_texture);
    start_button_sprite.setScale(0.6f, 0.6f);
    start_button_sprite.setOrigin(start_button_texture.getSize().x / 2.f, start_button_texture.getSize().y / 2.f);
    start_button_sprite.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f - 100.f);

    if (!scores_button_texture.loadFromFile("assets/scores_button.png")) {
        std::cerr << "Error loading scores_button.png" << std::endl;
    }
    scores_button_sprite.setTexture(scores_button_texture);
    scores_button_sprite.setScale(0.6f, 0.6f);
    scores_button_sprite.setOrigin(scores_button_texture.getSize().x / 2.f, scores_button_texture.getSize().y / 2.f);
    scores_button_sprite.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);

    if (!exit_button_texture.loadFromFile("assets/exit_button.png")) {
        std::cerr << "Error loading exit_button.png" << std::endl;
    }
    exit_button_sprite.setTexture(exit_button_texture);
    exit_button_sprite.setScale(0.6f, 0.6f);
    exit_button_sprite.setOrigin(exit_button_texture.getSize().x / 2.f, exit_button_texture.getSize().y / 2.f);
    exit_button_sprite.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f + 100.f);

    if (!you_lose_texture.loadFromFile("assets/you_lose.png")) {
        std::cerr << "Error loading you_lose.png" << std::endl;
    }
    you_lose_sprite.setTexture(you_lose_texture);
    you_lose_sprite.setScale(0.8f, 0.8f);
    you_lose_sprite.setOrigin(you_lose_texture.getSize().x / 2.f, you_lose_texture.getSize().y / 2.f);
    you_lose_sprite.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f - 100.f);

    back_button.setFont(font);
    back_button.setCharacterSize(30);
    back_button.setFillColor(sf::Color::Yellow);
    back_button.setString("Back");
    back_button.setOrigin(back_button.getGlobalBounds().width / 2.f, back_button.getGlobalBounds().height / 2.f);
    back_button.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT - 50.f);

    high_scores_text.setFont(font);
    high_scores_text.setCharacterSize(24);
    high_scores_text.setFillColor(sf::Color::White);
    high_scores_text.setPosition(50.f, 50.f);

    if (!info_button_texture.loadFromFile("assets/info.png")) {
        std::cerr << "Error loading info.png" << std::endl;
    }
    info_button_sprite.setTexture(info_button_texture);
    info_button_sprite.setScale(0.3f, 0.3f);
    info_button_sprite.setOrigin(info_button_texture.getSize().x / 2.f, info_button_texture.getSize().y / 2.f);
    info_button_sprite.setPosition(WIN_WIDTH - 50.f, 50.f);

    if (!sound_button_texture.loadFromFile("assets/sound.png")) {
        std::cerr << "Error loading sound.png" << std::endl;
    }
    sound_button_sprite.setTexture(sound_button_texture);
    sound_button_sprite.setScale(0.3f, 0.3f);
    sound_button_sprite.setOrigin(sound_button_texture.getSize().x / 2.f, sound_button_texture.getSize().y / 2.f);
    sound_button_sprite.setPosition(WIN_WIDTH - 120.f, 50.f);

    if (!instructions_window_texture.loadFromFile("assets/window.png")) {
        std::cerr << "Error loading window.png" << std::endl;
    }
    instructions_window_sprite.setTexture(instructions_window_texture);
    instructions_window_sprite.setOrigin(instructions_window_texture.getSize().x / 2.f, instructions_window_texture.getSize().y / 2.f);
    instructions_window_sprite.setPosition(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);

    instructions_text.setFont(font);
    instructions_text.setCharacterSize(30); // UPDATED: Reduced font size
    instructions_text.setFillColor(sf::Color::White);
    instructions_text.setString(
        "Instructions:\n\n"
        "Key A  -  Shoot\n\n"
        "Up Arrow  -  Move Up\n"
        "Down Arrow - Move Down\n"
        "Left Arrow - Move Left\n"
        "Right Arrow- Move Right"
    );
    instructions_text.setOrigin(instructions_text.getGlobalBounds().width / 2.f, instructions_text.getGlobalBounds().height / 2.f);
    instructions_text.setPosition(instructions_window_sprite.getPosition().x, instructions_window_sprite.getPosition().y - 60.f); // UPDATED: Adjusted position

    close_button_text.setFont(font);
    close_button_text.setCharacterSize(30);
    close_button_text.setFillColor(sf::Color::Yellow);
    close_button_text.setString("BACK");
    close_button_text.setOrigin(close_button_text.getGlobalBounds().width / 2.f, close_button_text.getGlobalBounds().height / 2.f);
    close_button_text.setPosition(instructions_window_sprite.getPosition().x, instructions_window_sprite.getPosition().y + 150.f);

    flap_buffer.loadFromFile("assets/flap.wav");
    dead_buffer.loadFromFile("assets/dead.mp3");
    shoot_buffer.loadFromFile("assets/shoot.wav");
    if (!click_buffer.loadFromFile("assets/click.mp3")) {
        std::cerr << "Error loading click.mp3" << std::endl;
    }
    if (!background_music.openFromFile("assets/background_music.mp3")) {
        std::cerr << "Error loading background_music.mpdl" << std::endl;
    }
    background_music.setLoop(true);
    background_music.setVolume(20.f);
    background_music.play();

    flap_sound.setBuffer(flap_buffer);
    dead_sound.setBuffer(dead_buffer);
    shoot_sound.setBuffer(shoot_buffer);
    click_sound.setBuffer(click_buffer);

    Missile::loadTexture();
    Meteor::loadTexture();
    Explosion::loadTextures();
    Projectile::loadTexture();
    Bomb::loadTexture();

    loadScores();
}

void Game::doProcessing(sf::Time& dt)
{
    scrolling_background.update(dt);

    for (auto it = explosions.begin(); it != explosions.end(); )
    {
        it->update(dt);
        if (it->isFinished())
        {
            it = explosions.erase(it);
        }
        else
        {
            ++it;
        }
    }

    switch (current_state) {
    case InGame:
        if (score_timer.getElapsedTime().asSeconds() >= 1.0f)
        {
            score++;
            score_text.setString("Score: " + toString(score));
            score_timer.restart();
        }

        if (missile_counter > missile_spawn_time)
        {
            missiles.emplace_back(
                static_cast<float>(WIN_WIDTH),
                static_cast<float>(missile_y_dist(rd)),
                missile_rotation_dist(rd)
            );
            missile_counter = 0;
        }
        missile_counter++;

        if (meteor_counter > meteor_spawn_time)
        {
            int num_meteors_to_spawn = meteor_burst_dist(rd);
            float base_spawn_x = static_cast<float>(WIN_WIDTH) + static_cast<float>(meteor_x_spawn_offset_dist(rd));

            std::vector<int> spawned_y_positions;
            int min_y_gap = 150;

            for (int i = 0; i < num_meteors_to_spawn; ++i)
            {
                int new_y;
                bool y_is_unique_and_spaced = false;
                int attempts = 0;
                const int max_attempts = 20;

                while (!y_is_unique_and_spaced && attempts < max_attempts)
                {
                    new_y = meteor_y_dist(rd);
                    y_is_unique_and_spaced = true;
                    for (int existing_y : spawned_y_positions)
                    {
                        if (std::abs(new_y - existing_y) < min_y_gap)
                        {
                            y_is_unique_and_spaced = false;
                            break;
                        }
                    }
                    attempts++;
                }

                if (y_is_unique_and_spaced)
                {
                    meteors.emplace_back(
                        base_spawn_x + (i * 50.f),
                        static_cast<float>(new_y)
                    );
                    spawned_y_positions.push_back(new_y);
                }
            }
            meteor_counter = 0;
        }
        meteor_counter++;

        if (bomb_counter > bomb_spawn_time)
        {
            int num_bombs_to_spawn = bomb_burst_dist(rd);
            float base_spawn_x = static_cast<float>(WIN_WIDTH) + static_cast<float>(bomb_x_spawn_offset_dist(rd));

            std::vector<int> spawned_y_positions;
            int min_y_gap = 80;

            for (int i = 0; i < num_bombs_to_spawn; ++i)
            {
                int new_y;
                bool y_is_unique_and_spaced = false;
                int attempts = 0;
                const int max_attempts = 20;

                while (!y_is_unique_and_spaced && attempts < max_attempts)
                {
                    new_y = bomb_y_dist(rd);
                    y_is_unique_and_spaced = true;
                    for (int existing_y : spawned_y_positions)
                    {
                        if (std::abs(new_y - existing_y) < min_y_gap)
                        {
                            y_is_unique_and_spaced = false;
                            break;
                        }
                    }
                    attempts++;
                }

                if (y_is_unique_and_spaced)
                {
                    bombs.emplace_back(
                        base_spawn_x + (i * 30.f),
                        static_cast<float>(new_y)
                    );
                    spawned_y_positions.push_back(new_y);
                }
            }
            bomb_counter = 0;
        }
        bomb_counter++;

        for (auto it = missiles.begin(); it != missiles.end(); )
        {
            it->update(dt);
            if (it->getRightBound() < 0)
            {
                it = missiles.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = meteors.begin(); it != meteors.end(); )
        {
            it->update(dt);
            if (it->getRightBound() < 0)
            {
                it = meteors.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = bombs.begin(); it != bombs.end(); )
        {
            it->update(dt);
            if (it->getRightBound() < 0)
            {
                it = bombs.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = projectiles.begin(); it != projectiles.end(); )
        {
            it->update(dt);
            if (it->getLeftBound() > WIN_WIDTH)
            {
                it = projectiles.erase(it);
            }
            else
            {
                ++it;
            }
        }

        checkCollisions();
        if (helicopter_visible)
        {
            helicopter.update(dt);
        }
        break;

    case Exploding:
        if (explosion_timer.getElapsedTime().asSeconds() >= EXPLOSION_DURATION)
        {
            current_state = GameOver;
        }
        break;

    case GameOver:
    case MainMenu:
    case Scores:
    case Instructions:
        break;
    }
}

void Game::startGameLoop()
{
    sf::Clock clock;
    while (win.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }

            switch (current_state) {
            case MainMenu:
                handleMainMenuEvents(event);
                break;
            case InGame:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        helicopter.moveHelicopterUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        helicopter.moveHelicopterDown();
                    }
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        helicopter.moveHelicopterLeft();
                    }
                    else if (event.key.code == sf::Keyboard::Right)
                    {
                        helicopter.moveHelicopterRight();
                    }
                    else if (event.key.code == sf::Keyboard::A)
                    {
                        if (projectile_fire_rate_timer.getElapsedTime().asSeconds() >= PROJECTILE_FIRE_RATE)
                        {
                            projectiles.emplace_back(
                                helicopter.getGlobalBounds().left + helicopter.getGlobalBounds().width,
                                helicopter.getGlobalBounds().top + helicopter.getGlobalBounds().height / 2.f
                            );
                            if (!is_muted) {
                                shoot_sound.play();
                            }
                            projectile_fire_rate_timer.restart();
                        }
                    }
                }
                else if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                    {
                        helicopter.stopVerticalMovement();
                    }
                    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                    {
                        helicopter.stopHorizontalMovement();
                    }
                }
                break;
            case Exploding:
                break;
            case GameOver:
                handleGameOverEvents(event);
                break;
            case Scores:
                handleScoresEvents(event);
                break;
            case Instructions:
                handleInstructionsEvents(event);
                break;
            }
        }

        doProcessing(dt);
        draw();
        win.display();
    }
}

void Game::draw()
{
    win.clear();
    scrolling_background.draw(win);

    switch (current_state) {
    case MainMenu:
        drawMainMenu();
        break;
    case InGame:
        for (Missile& missile : missiles)
        {
            missile.draw(win);
        }
        for (Meteor& meteor : meteors)
        {
            meteor.draw(win);
        }
        for (Bomb& bomb : bombs)
        {
            bomb.draw(win);
        }
        for (Projectile& projectile : projectiles)
        {
            projectile.draw(win);
        }
        if (helicopter_visible)
        {
            helicopter.draw(win);
        }
        for (Explosion& explosion : explosions)
        {
            explosion.draw(win);
        }
        win.draw(score_text);
        break;
    case Exploding:
        for (Missile& missile : missiles)
        {
            missile.draw(win);
        }
        for (Meteor& meteor : meteors)
        {
            meteor.draw(win);
        }
        for (Bomb& bomb : bombs)
        {
            bomb.draw(win);
        }
        for (Projectile& projectile : projectiles)
        {
            projectile.draw(win);
        }
        for (Explosion& explosion : explosions)
        {
            explosion.draw(win);
        }
        win.draw(score_text);
        break;
    case GameOver:
        win.draw(you_lose_sprite);
        for (Missile& missile : missiles)
        {
            missile.draw(win);
        }
        for (Meteor& meteor : meteors)
        {
            meteor.draw(win);
        }
        for (Bomb& bomb : bombs)
        {
            bomb.draw(win);
        }
        for (Projectile& projectile : projectiles)
        {
            projectile.draw(win);
        }
        if (helicopter_visible)
        {
            helicopter.draw(win);
        }
        for (Explosion& explosion : explosions)
        {
            explosion.draw(win);
        }
        drawGameOver();
        break;
    case Scores:
        drawScores();
        break;
    case Instructions:
        drawInstructions();
        break;
    }
}

void Game::checkCollisions()
{
    if (!helicopter_visible) return;

    for (auto proj_it = projectiles.begin(); proj_it != projectiles.end(); )
    {
        bool projectile_destroyed = false;
        for (auto missile_it = missiles.begin(); missile_it != missiles.end(); )
        {
            if (proj_it->getGlobalBounds().intersects(missile_it->getGlobalBounds()))
            {
                if (!is_muted) {
                    dead_sound.play();
                }
                explosions.emplace_back(missile_it->getGlobalBounds().getPosition(), explosion_type_dist(rd));
                missile_it = missiles.erase(missile_it);
                proj_it = projectiles.erase(proj_it);
                projectile_destroyed = true;
                break;
            }
            else
            {
                ++missile_it;
            }
        }
        if (!projectile_destroyed)
        {
            ++proj_it;
        }
    }

    for (auto proj_it = projectiles.begin(); proj_it != projectiles.end(); )
    {
        bool projectile_destroyed = false;
        for (auto bomb_it = bombs.begin(); bomb_it != bombs.end(); )
        {
            if (proj_it->getGlobalBounds().intersects(bomb_it->getGlobalBounds()))
            {
                if (!is_muted) {
                    dead_sound.play();
                }
                explosions.emplace_back(bomb_it->getGlobalBounds().getPosition(), explosion_type_dist(rd));
                bomb_it = bombs.erase(bomb_it);
                proj_it = projectiles.erase(proj_it);
                projectile_destroyed = true;
                break;
            }
            else
            {
                ++bomb_it;
            }
        }
        if (!projectile_destroyed)
        {
            ++proj_it;
        }
    }

    if (helicopter_visible)
    {
        for (auto it = missiles.begin(); it != missiles.end(); ++it)
        {
            if (helicopter.getGlobalBounds().intersects(it->getGlobalBounds()))
            {
                if (!is_muted) {
                    dead_sound.play();
                }
                explosions.emplace_back(helicopter.getGlobalBounds().getPosition(), explosion_type_dist(rd));
                helicopter_visible = false;
                current_state = Exploding;
                explosion_timer.restart();
                saveScore();
                missiles.erase(it);
                return;
            }
        }

        for (auto it = meteors.begin(); it != meteors.end(); ++it)
        {
            if (helicopter.getGlobalBounds().intersects(it->getGlobalBounds()))
            {
                if (!is_muted) {
                    dead_sound.play();
                }
                explosions.emplace_back(helicopter.getGlobalBounds().getPosition(), explosion_type_dist(rd));
                helicopter_visible = false;
                current_state = Exploding;
                explosion_timer.restart();
                saveScore();
                meteors.erase(it);
                return;
            }
        }

        for (auto it = bombs.begin(); it != bombs.end(); ++it)
        {
            if (helicopter.getGlobalBounds().intersects(it->getGlobalBounds()))
            {
                if (!is_muted) {
                    dead_sound.play();
                }
                explosions.emplace_back(helicopter.getGlobalBounds().getPosition(), explosion_type_dist(rd));
                helicopter_visible = false;
                current_state = Exploding;
                explosion_timer.restart();
                saveScore();
                bombs.erase(it);
                return;
            }
        }
    }
}

void Game::restartGame()
{
    helicopter.resetHelicopterPosition();
    missiles.clear();
    meteors.clear();
    bombs.clear();
    explosions.clear();
    projectiles.clear();
    helicopter_visible = true;
    score = 0;
    score_text.setString("Score: 0");
    score_text.setPosition(15.f, 15.f);
    current_state = InGame;
    helicopter.setShouldFly(true);
    score_timer.restart();
}

std::string Game::toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void Game::drawMainMenu()
{
    win.draw(start_button_sprite);
    win.draw(scores_button_sprite);
    win.draw(exit_button_sprite);
    win.draw(info_button_sprite);
    win.draw(sound_button_sprite);
}

void Game::handleMainMenuEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (start_button_sprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = InGame;
            restartGame();
        }
        else if (scores_button_sprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = Scores;
        }
        else if (exit_button_sprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            win.close();
        }
        else if (info_button_sprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = Instructions;
        }
        else if (sound_button_sprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            toggleMute();
        }
    }
}

void Game::drawGameOver()
{
    win.draw(you_lose_sprite);
    win.draw(restart_text);
    score_text.setPosition(WIN_WIDTH / 2.f - score_text.getGlobalBounds().width / 2.f, WIN_HEIGHT / 2.f + 50.f);
    score_text.setString("Final Score: " + toString(score));
    win.draw(score_text);
}

void Game::handleGameOverEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (restart_text.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = MainMenu;
            helicopter.resetHelicopterPosition();
            missiles.clear();
            meteors.clear();
            explosions.clear();
            projectiles.clear();
            helicopter_visible = true;
        }
    }
}

void Game::drawScores()
{
    win.draw(high_scores_text);
    win.draw(back_button);
}

void Game::handleScoresEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (back_button.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = MainMenu;
        }
    }
}

void Game::saveScore()
{
    high_scores.push_back(score);
    std::sort(high_scores.rbegin(), high_scores.rend());

    std::ofstream file(scores_filename);
    if (file.is_open())
    {
        for (size_t i = 0; i < high_scores.size() && i < 5; ++i)
        {
            file << high_scores[i] << std::endl;
        }
        file.close();
    }
    loadScores();
}

void Game::loadScores()
{
    high_scores.clear();
    std::ifstream file(scores_filename);
    if (file.is_open())
    {
        int loaded_score;
        while (file >> loaded_score)
        {
            high_scores.push_back(loaded_score);
        }
        file.close();
    }

    std::sort(high_scores.rbegin(), high_scores.rend());

    std::stringstream ss;
    ss << "High Scores:" << std::endl;
    for (size_t i = 0; i < high_scores.size(); ++i)
    {
        ss << i + 1 << ". " << high_scores[i] << std::endl;
    }
    high_scores_text.setString(ss.str());
}

void Game::drawInstructions()
{
    win.draw(instructions_window_sprite);
    win.draw(instructions_text);
    win.draw(close_button_text);
}

void Game::handleInstructionsEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (close_button_text.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            if (!is_muted) {
                click_sound.play();
            }
            current_state = MainMenu;
        }
    }
}

void Game::toggleMute()
{
    is_muted = !is_muted;
    if (is_muted)
    {
        background_music.setVolume(0.f);
        flap_sound.setVolume(0.f);
        dead_sound.setVolume(0.f);
        shoot_sound.setVolume(0.f);
        click_sound.setVolume(0.f);
        sound_button_sprite.setColor(sf::Color(128, 128, 128));
    }
    else
    {
        background_music.setVolume(20.f);
        flap_sound.setVolume(100.f);
        dead_sound.setVolume(100.f);
        shoot_sound.setVolume(100.f);
        click_sound.setVolume(100.f);
        sound_button_sprite.setColor(sf::Color::White);
    }
}