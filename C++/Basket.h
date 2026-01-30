#include <SFML/Graphics.hpp>
#include <string>

class Basket {
public:
    Basket();
    bool loadTexture(const std::string& filename);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    void setSpeed(float newSpeed);
    void move(float xOffset, float windowWidth);
    float getSpeed() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};