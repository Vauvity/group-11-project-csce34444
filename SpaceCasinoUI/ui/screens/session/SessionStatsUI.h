#pragma once

#include <SFML/Graphics.hpp>
#include "../../../core/session/SessionStats.h"

class SessionStatsUI
{
public:
    explicit SessionStatsUI(sf::Font& sharedFont);
    void handleMouseClick(sf::Vector2f mousePos, bool& backToMenu);
    void draw(sf::RenderWindow& window, const SessionStats& sessionStats);

private:
    sf::Font& font;
    sf::Text titleText;
    sf::Text subTitleText;
    sf::RectangleShape backButton;
    sf::Text backText;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void drawPanel(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, const std::string& title) const;
    void drawStatLine(sf::RenderWindow& window, const std::string& label, const std::string& value, float x, float y, unsigned int size = 20) const;
    std::string money(double value) const;
    std::string percent(double value) const;
};
