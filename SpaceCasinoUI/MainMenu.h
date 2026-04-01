#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class MainMenu
{
public:
    explicit MainMenu(sf::Font& sharedFont);

    void handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();

    bool hasValidBankroll() const;
    double getEnteredBankroll() const;

    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;

    sf::Text titleText;
    sf::Text bankrollLabelText;
    sf::Text bankrollInputText;
    sf::Text bankrollHintText;
    sf::Text errorText;

    sf::RectangleShape bankrollBox;
    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;

    sf::Text startText;
    sf::Text exitText;

    std::string bankrollInput;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void refreshBankrollText();
};