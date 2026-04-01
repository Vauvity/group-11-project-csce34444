#pragma once

#include <SFML/Graphics.hpp>

class MainMenu
{
public:
    explicit MainMenu(sf::Font& sharedFont);

    void handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame);
    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;

    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;
    sf::Text startText;
    sf::Text exitText;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
};