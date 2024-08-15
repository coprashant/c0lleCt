#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // For sound effects
#include <vector>
#include "Basket.h"
#include "Egg.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void renderGameOver();
    void resetGame();
    void spawnEgg();
    void checkEggFall();

    sf::RenderWindow window;
    Basket basket;
    std::vector<Egg> eggs;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture gameOverBackgroundTexture;
    sf::Sprite gameOverBackgroundSprite;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Music backgroundMusic;
    sf::SoundBuffer eggCatchSoundBuffer;
    sf::Sound eggCatchSound;
    sf::SoundBuffer eggMissSoundBuffer;
    sf::Sound eggMissSound;
    sf::Text levelText;

    int score;
    float eggSpeed;
    bool gameOver;
};
