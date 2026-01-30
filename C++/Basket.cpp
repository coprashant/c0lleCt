#include "Basket.h"
#include <SFML/Graphics.hpp>
#include<iostream>

Basket::Basket() : speed(4.0f) {
    if (!texture.loadFromFile("resources/images/basket.png")) {
        std::cerr << "Error loading texture from file." << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(400, 550); // Starting position
    sprite.setScale(0.4f, 0.4f);
}

bool Basket::loadTexture(const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading texture from file: " << filename << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void Basket::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Basket::move(float xOffset, float windowWidth) {
        sf::Vector2f pos = sprite.getPosition();
        float newX = pos.x + xOffset;

        // Keep the basket inside the screen boundaries
        if (newX >= 0 && newX + sprite.getGlobalBounds().width <= windowWidth) {
            sprite.setPosition(newX, pos.y);
        }
}

void Basket::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Basket::getBounds() const {
    return sprite.getGlobalBounds();
}
