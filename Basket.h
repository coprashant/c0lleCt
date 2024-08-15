#pragma once
#include <SFML/Graphics.hpp>

class Basket {
public:
    Basket();
    bool loadTexture(const std::string& filename);
    void setPosition(float x, float y);
    void moveLeft(float dx, float screenWidth);
    void moveRight(float dx, float screenWidth);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};
