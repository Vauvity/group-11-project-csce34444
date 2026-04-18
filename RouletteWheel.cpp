#include "RouletteWheel.h"

float getAngle(int n) {
    return (360.f / 37.f) * n;
}

void RouletteWheel::startSpin(int result) {
    targetRotation = rotation + 5 * 360.f + getAngle(result);
    spinning = true;
}

void RouletteWheel::update(float dt) {
    if (!spinning) return;

    float speed = 500.f;

    if (rotation < targetRotation) {
        rotation += speed * dt;
    } else {
        rotation = targetRotation;
        spinning = false;
    }
}

void RouletteWheel::draw(sf::RenderWindow& window) {
    sf::CircleShape wheel(100);
    wheel.setOrigin(100,100);
    wheel.setPosition(750,250);
    wheel.setRotation(rotation);
    wheel.setFillColor(sf::Color::White);
    window.draw(wheel);
}
