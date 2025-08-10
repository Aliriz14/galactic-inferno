#include<SFML/Graphics.hpp>
#include"header-files/Globals.h"
#include"header-files/Game.h"
#include"header-files/Helicopter.h"
#include"header-files/Missile.h"
// #include"Missile.h" // Not strictly necessary here as Game.h includes it

int main()
{
    sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Galactic inferno");
    Game game(win);
    game.startGameLoop();
    return 0;
}