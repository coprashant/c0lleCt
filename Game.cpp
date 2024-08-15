#include "Game.h"
#include <cmath> // For std::pow

Game::Game() : window(sf::VideoMode(1000, 800), "c0lleCt"), score(0), eggSpeed(0.8f), gameOver(false) {
    // Load and setup the background texture
    if (!backgroundTexture.loadFromFile("resources/images/background.png")) {
        // Handle error loading background texture
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ensure the background sprite is stretched to fill the window
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load and setup the font
    if (!font.loadFromFile("resources/font/game_over.ttf")) {

    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(80);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(10, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(80);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setPosition(window.getSize().x - 200, 10);

    // Setup the Game Over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Blue);
    gameOverText.setString("Game Over!\n\nYour Score was: " + std::to_string(score) + "\nPress R to Restart\nPress Esc to Exit");
    gameOverText.setPosition(
        window.getSize().x / 1.6f - gameOverText.getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f - gameOverText.getLocalBounds().height / 2.0f);

        // Load and setup the game over background texture
    if (!gameOverBackgroundTexture.loadFromFile("resources/images/game_over_background.png")) {

    }
    gameOverBackgroundSprite.setTexture(gameOverBackgroundTexture);

    // Ensure the game over background sprite is stretched to fill the window
    gameOverBackgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / gameOverBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / gameOverBackgroundTexture.getSize().y

    );

    // Load and setup the basket texture
    if (!basket.loadTexture("resources/images/basket.png")) {
        // Handle error loading basket texture
    }
    basket.setPosition(
        (window.getSize().x - basket.getBounds().width) / 2.0f,
        window.getSize().y - basket.getBounds().height - 20
    );

    // Load and setup sounds
    if (!backgroundMusic.openFromFile("resources/sounds/background.wav")) {
        // Handle error loading background music
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    if (!eggCatchSoundBuffer.loadFromFile("resources/sounds/egg_catch.wav")) {
        // Handle error loading egg catch sound
    }
    eggCatchSound.setBuffer(eggCatchSoundBuffer);

    if (!eggMissSoundBuffer.loadFromFile("resources/sounds/egg_miss.wav")) {
        // Handle error loading egg miss sound
    }
    eggMissSound.setBuffer(eggMissSoundBuffer);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        if (!gameOver) {
            update();
        }
        render();
        sf::sleep(sf::milliseconds(5)); // Slow down the game a bit
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && gameOver) {
            if (event.key.code == sf::Keyboard::R) {
                resetGame(); // Reset game when 'R' is pressed
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close(); // Exit game when 'Esc' is pressed
            }
        }
    }

    if (!gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            basket.moveLeft(1.0f, window.getSize().x); // Provide both arguments
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            basket.moveRight(1.0f, window.getSize().x); // Provide both arguments
        }
    }
}

void Game::update() {
    checkEggFall();

    if (eggs.empty()) {
        spawnEgg();
    }

    for (auto it = eggs.begin(); it != eggs.end(); ) {
        it->update(eggSpeed);
        if (it->getBounds().intersects(basket.getBounds())) {
            score++;
            eggCatchSound.play(); // Play catch sound
            it = eggs.erase(it); // Remove the egg if caught
            spawnEgg(); // Spawn a new egg
        } else if (it->getBounds().top > window.getSize().y || it->getBounds().top > basket.getBounds().top) {
            eggMissSound.play(); // Play miss sound
            gameOver = true; // End the game if egg falls out of bounds or misses
            it = eggs.erase(it);
        } else {
            ++it;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));

    int level = (score / 10) + 1; // Level starts at 1
    levelText.setString("Level: " + std::to_string(level));

    if (score % 10 == 0 && score != 0) {
        eggSpeed = 0.8f * std::pow(1.4f, (score / 10) - 1);
    }
}

void Game::render() {
    window.clear();
    if (gameOver) {
        window.draw(gameOverBackgroundSprite); // Draw game over background
    } else {
        window.draw(backgroundSprite); // Draw main background
        basket.draw(window);
    }


    for (const auto& egg : eggs) {
        egg.draw(window);
    }

    window.draw(scoreText);
    window.draw(levelText); // Draw level text

    if (gameOver) {
        renderGameOver(); // Draw Game Over text
    }

    window.display();
}

void Game::resetGame() {
    score = 0;
    eggSpeed = 0.8f;
    gameOver = false;
    eggs.clear();
    spawnEgg();
}

void Game::spawnEgg() {
    float startX = static_cast<float>(rand() % (window.getSize().x - 100));
    eggs.emplace_back(startX);
}

void Game::renderGameOver() {
    window.draw(gameOverText);
}

void Game::checkEggFall() {
    // Check for eggs falling outside the bounds
    for (auto it = eggs.begin(); it != eggs.end(); ) {
        if (it->getBounds().top > window.getSize().y) {
            eggMissSound.play(); // Play miss sound
            gameOver = true; // End the game if egg falls out of bounds
            it = eggs.erase(it);
        } else {
            ++it;
        }
    }
}
