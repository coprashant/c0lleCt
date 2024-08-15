#include "Egg.h"

Egg::Egg(float startX) {
    texture.loadFromFile("resources/images/egg.png");
    sprite.setTexture(texture);
    sprite.setPosition(startX, 0);
    sprite.setScale(0.5f, 0.5f);
}

void Egg::update(float speed) {
    sprite.move(0, speed);
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
