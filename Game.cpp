#include "Game.h"
#include <cmath>

Game::Game() : window(sf::VideoMode(1000, 800), "c0lleCt"), score(0), eggSpeed(0.8f), gameOver(false), isPaused(false) {
    // Load and setup the background texture
    if (!backgroundTexture.loadFromFile("resources/images/background.png")) {
    }
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load and setup the font
    if (!font.loadFromFile("resources/font/game_over.ttf")) {

    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(80);
    scoreText.setFillColor(sf::Color(255, 165, 0));
    scoreText.setPosition(window.getSize().x - 250, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(80);
    levelText.setFillColor(sf::Color(255, 165, 0));
    levelText.setPosition(window.getSize().x - 250, scoreText.getPosition().y + scoreText.getLocalBounds().height + 30);

    // Setup the Game Over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Blue);
    gameOverText.setString("Game Over!\n\nYour Score was: " + std::to_string(score) + "\nPress R to Restart\nPress Esc to Exit");
    gameOverText.setPosition(
        window.getSize().x / 1.6f - gameOverText.getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f - gameOverText.getLocalBounds().height / 2.0f
    );

    // Load and setup the game over background texture
    if (!gameOverBackgroundTexture.loadFromFile("resources/images/game_over_background.png")) {
        // Handle error loading game over background texture
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

    // Setup Pause/Options Button
    pauseButton.setSize(sf::Vector2f(150, 50));
    pauseButton.setFillColor(sf::Color::Red);
    pauseButton.setPosition(10, 5); // Top left corner

    pauseButtonText.setFont(font);
    pauseButtonText.setCharacterSize(50);
    pauseButtonText.setFillColor(sf::Color::White);
    pauseButtonText.setString("| |");

    // Center the text within the button
    sf::FloatRect textBounds = pauseButtonText.getLocalBounds();
    pauseButtonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                              textBounds.top + textBounds.height / 2.0f);
    pauseButtonText.setPosition(
        pauseButton.getPosition().x + pauseButton.getSize().x / 2.0f,
        pauseButton.getPosition().y + pauseButton.getSize().y / 2.0f
    );

    // Setup Options Menu
    optionsMenu.setSize(sf::Vector2f(300, 200));
    optionsMenu.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent background
    optionsMenu.setPosition(window.getSize().x / 2.0f - 150, window.getSize().y / 2.0f - 100);

    continueButtonText.setFont(font);
    continueButtonText.setCharacterSize(50);
    continueButtonText.setFillColor(sf::Color::White);
    continueButtonText.setString("Continue");
    continueButtonText.setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f - 60);

    endGameButtonText.setFont(font);
    endGameButtonText.setCharacterSize(50);
    endGameButtonText.setFillColor(sf::Color::White);
    endGameButtonText.setString("End Game");
    endGameButtonText.setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f + 25);
}

void Game::resizeView() {
    float windowRatio = window.getSize().x / static_cast<float>(window.getSize().y);
    float viewRatio = window.getDefaultView().getSize().x / window.getDefaultView().getSize().y;
    float sizeX = 1.0f;
    float sizeY = 1.0f;
    float posX = 0.0f;
    float posY = 0.0f;

    bool horizontalSpacing = windowRatio > viewRatio;
    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    sf::View view(sf::FloatRect(0, 0, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y));
    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    window.setView(view);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        if (!gameOver && !isPaused) {
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
        if (event.type == sf::Event::Resized) {
            resizeView();
        }
        // Check if the mouse button is clicked within the pause button
        if (event.type == sf::Event::MouseButtonPressed && !gameOver) {
            if (pauseButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isPaused = !isPaused;
                pauseButtonText.setString(isPaused ? "Continue" : "| |");
            }
        }

        // Check if mouse clicks are within options menu
        if (event.type == sf::Event::MouseButtonPressed && isPaused) {
            if (continueButtonText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isPaused = false;
                pauseButtonText.setString("| |");
            }
            else if (endGameButtonText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                window.close();
            }
        }

        if (event.type == sf::Event::KeyPressed && gameOver) {
            if (event.key.code == sf::Keyboard::R) {
                resetGame(); // Reset game when 'R' is pressed
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close(); // Exit game when 'Esc' is pressed
            }
        }
    }

    if (!gameOver && !isPaused) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            basket.moveLeft(1.0f, window.getSize().x);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            basket.moveRight(1.0f, window.getSize().x);
        }
    }
}

void Game::update() {

    if (eggs.empty() || eggs.back().getBounds().top > 100) {
        spawnEgg(800.0f * std::rand() / RAND_MAX, 0); // Random position
    }

    for (auto it = eggs.begin(); it != eggs.end(); ) {
        it->update(eggSpeed);

        // Ensure the egg stays within the window bounds horizontally
        if (it->getBounds().left < 0) {
            it->setPosition(0, it->getPosition().y);
        } else if (it->getBounds().left + it->getBounds().width > window.getSize().x) {
            it->setPosition(window.getSize().x - it->getBounds().width, it->getPosition().y);
        }

        if (it->getBounds().intersects(basket.getBounds())) {
            score++;
            eggCatchSound.play();
            it = eggs.erase(it);
        } else if (it->isOutOfBounds(window.getSize().y)) {
            eggMissSound.play();
            it = eggs.erase(it);
        } else {
            ++it;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
    levelText.setString("Level: " + std::to_string(score / 10 + 1)); // Increment level every 10 points

    int level = score / 10 + 1;
    if (score % 10 == 0 && score != 0) {
        eggSpeed = std::pow(1.3f, level); // Increase speed by 1.3x per level
    }

    if (checkEggFall()) {
        gameOver = true;
        gameOverText.setString("Game Over!\n\nYour Score was: " + std::to_string(score) + "\nPress R to Restart\nPress Esc to Exit");
    }
}

void Game::spawnEgg(float xPos, float yPos) {
    int level = score / 10 + 1;
    int eggCount = std::ceil(level / 3.0f); // Increase number of eggs every 3 levels

    if (eggs.size() < eggCount) {
        // Ensure egg spawns within the screen width
        float eggWidth = 0;

        if (!sf::Texture().loadFromFile("resources/images/egg.png")) {

        }
        eggWidth = sf::Texture().getSize().x * 0.4f; // Egg width scaled
        xPos = std::max(0.0f, std::min(xPos, window.getSize().x - eggWidth));

        // Pass window size to the Egg constructor
        eggs.emplace_back(xPos, yPos, window.getSize());
    }
}



void Game::render() {
    window.clear();
    window.draw(backgroundSprite);

    for (auto& egg : eggs) {
        egg.draw(window);
    }

    basket.draw(window);

    window.draw(scoreText);
    window.draw(levelText);

    if (gameOver) {
        window.draw(gameOverBackgroundSprite);
        window.draw(gameOverText);
    }

    // Draw the pause/options menu button
    window.draw(pauseButton);
    window.draw(pauseButtonText);

    // Draw the options menu if paused
    if (isPaused) {
        window.draw(optionsMenu);
        window.draw(continueButtonText);
        window.draw(endGameButtonText);
    }

    window.display();
}

void Game::resetGame() {
    eggs.clear();
    score = 0;
    eggSpeed = 0.8f;
    gameOver = false;
}

bool Game::checkEggFall() const {
    return std::any_of(eggs.begin(), eggs.end(), [&](const Egg& egg) {
        return egg.getBounds().top + egg.getBounds().height > window.getSize().y;
    });
}
