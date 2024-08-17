#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    void resetGame();
    bool checkEggFall() const;
    void spawnEgg(float xPos, float yPos);
    void resizeView();

    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    Basket basket;
    std::vector<Egg> eggs;
    sf::Vector2u backgroundSize;

    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Text gameOverText;

    sf::Texture gameOverBackgroundTexture;
    sf::Sprite gameOverBackgroundSprite;

    sf::RectangleShape pauseButton;
    sf::Text pauseButtonText;

    sf::RectangleShape optionsMenu;
    sf::Text continueButtonText;
    sf::Text endGameButtonText;

    sf::Music backgroundMusic;
    sf::SoundBuffer eggCatchSoundBuffer;
    sf::SoundBuffer eggMissSoundBuffer;
    sf::Sound eggCatchSound;
    sf::Sound eggMissSound;

    int score;
    float eggSpeed;
    bool gameOver;
    bool isPaused;
};
