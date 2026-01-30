#include <SFML/Graphics.hpp>

class Egg {
public:
    Egg(float startX, float startY, const sf::Vector2u& windowSize, float speed, const sf::Texture& texture);
    void update(float speed);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isOutOfBounds(float screenHeight) const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    float speed;
    sf::Vector2u windowSize;
};