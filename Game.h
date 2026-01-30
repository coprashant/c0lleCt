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
    void update(float deltaTime);  // Pass deltaTime for egg movement
    void render();
    void renderMenu();
    void resetGame();
    bool checkEggFall() const;
    void spawnEgg(float xPos, float yPos);
    void resizeView();

    // SFML window, graphics, and text elements
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    Basket basket;
    sf::Texture eggTexture; 
    std::vector<Egg> eggs;
    sf::Vector2u backgroundSize;

    // UI elements
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

    bool isMenuActive = true; // Start with the menu active
    sf::RectangleShape playButton;
    sf::Text playButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    // Shadows for the buttons
    sf::RectangleShape playButtonShadow;
    sf::RectangleShape exitButtonShadow;

    // Audio elements
    sf::Music backgroundMusic;
    sf::SoundBuffer eggCatchSoundBuffer;
    sf::SoundBuffer eggMissSoundBuffer;
    sf::Sound eggCatchSound;
    sf::Sound eggMissSound;

    // Game-related variables
    int score;            // Player score
    float eggSpeed;       // Speed of eggs, resets and increases every 3 levels
    bool gameOver;        // Tracks if the game is over
    bool isPaused;        // Tracks if the game is paused
    float backgroundWidth;
    float backgroundHeight;
    int lastLevel;        // Tracks the last level to manage egg speed
    static int previousLevel;

    // UI element positions
    sf::Vector2f playButtonPosition;
    sf::Vector2f exitButtonPosition;
};
