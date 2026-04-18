#pragma once
#include <SFML/Graphics.hpp>

class RouletteWheel {
private:
    float rotation = 0;
    float targetRotation = 0;
    bool spinning = false;

public:
    void startSpin(int result);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isSpinning() const { return spinning; }
};
