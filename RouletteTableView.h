#pragma once
#include <SFML/Graphics.hpp>
#include "RouletteState.h"

class RouletteTableView {
private:
    sf::Font font;

public:
    RouletteTableView();
    void draw(sf::RenderWindow& window, const RouletteState& state);
    void handleClick(sf::Vector2f pos, RouletteState& state);
};
