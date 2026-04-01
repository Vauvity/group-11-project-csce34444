#pragma once

#include <SFML/Graphics.hpp>

class GameSelect
{
public:
    explicit GameSelect(sf::Font& sharedFont);

    void handleMouseClick(sf::Vector2f mousePos, bool& openBlackjack, bool& openSlots, bool& backToMain);
    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;

    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text messageText;

    sf::RectangleShape blackjackButton;
    sf::RectangleShape rouletteButton;
    sf::RectangleShape slotsButton;
    sf::RectangleShape backButton;

    sf::Text blackjackText;
    sf::Text rouletteText;
    sf::Text slotsText;
    sf::Text backText;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
};