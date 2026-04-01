#include "MainMenu.h"

MainMenu::MainMenu(sf::Font& sharedFont)
    : font(sharedFont),
    titleText(font, "SPACE CASINO", 54),
    startText(font, "START GAME", 22),
    exitText(font, "EXIT", 22)
{
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 298.f, 110.f });

    startButton.setSize({ 300.f, 80.f });
    startButton.setPosition({ 350.f, 300.f });
    startButton.setFillColor(sf::Color(60, 60, 180));

    exitButton.setSize({ 300.f, 80.f });
    exitButton.setPosition({ 350.f, 420.f });
    exitButton.setFillColor(sf::Color(170, 50, 50));

    startText.setFillColor(sf::Color::White);
    exitText.setFillColor(sf::Color::White);

    centerTextInButton(startText, startButton);
    centerTextInButton(exitText, exitButton);
}

void MainMenu::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonPos = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();

    text.setPosition({
        buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.f - textBounds.position.x,
        buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.f - textBounds.position.y - 2.f
        });
}

void MainMenu::handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame)
{
    if (startButton.getGlobalBounds().contains(mousePos))
    {
        startGame = true;
    }
    else if (exitButton.getGlobalBounds().contains(mousePos))
    {
        exitGame = true;
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(0, 85, 20));
    window.draw(background);

    window.draw(titleText);
    window.draw(startButton);
    window.draw(exitButton);
    window.draw(startText);
    window.draw(exitText);
}