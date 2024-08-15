#pragma once
#include <SFML/Graphics.hpp>

class Egg {
public:
    Egg(float startX);
    void update(float speed);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isOutOfBounds(float screenHeight) const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
};
