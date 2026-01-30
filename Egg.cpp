#include "Egg.h"

Egg::Egg(float startX, float startY, const sf::Vector2u& windowSize, float speed, const sf::Texture& texture) 
    : windowSize(windowSize), speed(speed) {
    
    sprite.setTexture(texture); 
    sprite.setScale(0.4f, 0.4f);

    // Boundary check for spawning
    if (startX + sprite.getGlobalBounds().width > windowSize.x) {
        startX = windowSize.x - sprite.getGlobalBounds().width;
    } else if (startX < 0) {
        startX = 0;
    }

    sprite.setPosition(startX, startY);
}

void Egg::update(float deltaTime) {
    float fallingSpeed = 400.0f; 
    sprite.move(0, fallingSpeed * deltaTime);

    if (sprite.getPosition().x < 0) {
        sprite.setPosition(0, sprite.getPosition().y);
    }
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowSize.x) {
        sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}


void Egg::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Egg::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Egg::isOutOfBounds(float screenHeight) const {
    return sprite.getPosition().y > screenHeight;
}
void Egg::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Egg::getPosition() const {
    return sprite.getPosition();
}