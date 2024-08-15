#include "Basket.h"

Basket::Basket() : speed(2.0f) {
    texture.loadFromFile("resources/images/basket.png");
    sprite.setTexture(texture);
    sprite.setPosition(400, 550); // Starting position
    sprite.setScale(0.8f, 0.8f);
}

bool Basket::loadTexture(const std::string& filename) {
    return texture.loadFromFile(filename);
}

void Basket::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Basket::moveLeft(float dx, float screenWidth) {
    if (sprite.getPosition().x > 0) {
        sprite.move(-dx * speed, 0);
    }
}

void Basket::moveRight(float dx, float screenWidth) {
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < screenWidth) {
        sprite.move(dx * speed, 0);
    }
}

void Basket::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Basket::getBounds() const {
    return sprite.getGlobalBounds();
}
