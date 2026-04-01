#include "GameSelect.h"

GameSelect::GameSelect(sf::Font& sharedFont)
    : font(sharedFont),
    titleText(font, "CHOOSE YOUR GAME", 48),
    subtitleText(font, "Welcome to the casino floor", 20),
    messageText(font, "", 18),
    blackjackText(font, "BLACKJACK", 22),
    rouletteText(font, "ROULETTE", 22),
    slotsText(font, "SLOTS", 22),
    backText(font, "BACK", 22)
{
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 285.f, 85.f });

    subtitleText.setFillColor(sf::Color(235, 220, 90));
    subtitleText.setPosition({ 350.f, 145.f });

    messageText.setFillColor(sf::Color::Yellow);
    messageText.setPosition({ 315.f, 670.f });

    blackjackButton.setSize({ 320.f, 80.f });
    blackjackButton.setPosition({ 340.f, 220.f });
    blackjackButton.setFillColor(sf::Color(45, 130, 60));

    rouletteButton.setSize({ 320.f, 80.f });
    rouletteButton.setPosition({ 340.f, 330.f });
    rouletteButton.setFillColor(sf::Color(150, 80, 30));

    slotsButton.setSize({ 320.f, 80.f });
    slotsButton.setPosition({ 340.f, 440.f });
    slotsButton.setFillColor(sf::Color(110, 35, 140));

    backButton.setSize({ 220.f, 65.f });
    backButton.setPosition({ 390.f, 575.f });
    backButton.setFillColor(sf::Color(110, 110, 110));

    blackjackText.setFillColor(sf::Color::White);
    rouletteText.setFillColor(sf::Color::White);
    slotsText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);

    centerTextInButton(blackjackText, blackjackButton);
    centerTextInButton(rouletteText, rouletteButton);
    centerTextInButton(slotsText, slotsButton);
    centerTextInButton(backText, backButton);
}

void GameSelect::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonPos = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();

    text.setPosition({
        buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.f - textBounds.position.x,
        buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.f - textBounds.position.y - 2.f
        });
}

void GameSelect::handleMouseClick(sf::Vector2f mousePos, bool& openBlackjack, bool& openSlots, bool& backToMain)
{
    openBlackjack = false;
    openSlots = false;
    backToMain = false;

    if (blackjackButton.getGlobalBounds().contains(mousePos))
    {
        openBlackjack = true;
        messageText.setString("");
    }
    else if (rouletteButton.getGlobalBounds().contains(mousePos))
    {
        messageText.setString("Roulette does not work right now.");
    }
    else if (slotsButton.getGlobalBounds().contains(mousePos))
    {
        openSlots = true;
        messageText.setString("");
    }
    else if (backButton.getGlobalBounds().contains(mousePos))
    {
        backToMain = true;
        messageText.setString("");
    }
}

void GameSelect::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(0, 85, 20));
    window.draw(background);

    sf::RectangleShape topLine({ 700.f, 3.f });
    topLine.setPosition({ 150.f, 185.f });
    topLine.setFillColor(sf::Color(220, 180, 40));
    window.draw(topLine);

    sf::RectangleShape bottomLine({ 700.f, 3.f });
    bottomLine.setPosition({ 150.f, 550.f });
    bottomLine.setFillColor(sf::Color(220, 180, 40));
    window.draw(bottomLine);

    window.draw(titleText);
    window.draw(subtitleText);

    window.draw(blackjackButton);
    window.draw(rouletteButton);
    window.draw(slotsButton);
    window.draw(backButton);

    window.draw(blackjackText);
    window.draw(rouletteText);
    window.draw(slotsText);
    window.draw(backText);

    window.draw(messageText);
}