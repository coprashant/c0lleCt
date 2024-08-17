#pragma once
#include <SFML/Graphics.hpp>

class Egg {
public:
    Egg(float startX, float startY, const sf::Vector2u& windowSize);
    void update(float speed);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isOutOfBounds(float screenHeight) const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    sf::Vector2u windowSize;
};
