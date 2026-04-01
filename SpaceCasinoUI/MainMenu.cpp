#include "MainMenu.h"
#include <cctype>

MainMenu::MainMenu(sf::Font& sharedFont)
    : font(sharedFont),
    titleText(font, "SPACE CASINO", 54),
    bankrollLabelText(font, "ENTER STARTING BANKROLL", 24),
    bankrollInputText(font, "", 28),
    bankrollHintText(font, "Type numbers only. Example: 1000", 18),
    errorText(font, "", 18),
    startText(font, "START GAME", 22),
    exitText(font, "EXIT", 22),
    bankrollInput("1000")
{
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 298.f, 90.f });

    bankrollLabelText.setFillColor(sf::Color(235, 220, 90));
    bankrollLabelText.setPosition({ 315.f, 205.f });

    bankrollBox.setSize({ 320.f, 58.f });
    bankrollBox.setPosition({ 340.f, 245.f });
    bankrollBox.setFillColor(sf::Color(20, 20, 60));
    bankrollBox.setOutlineThickness(2.f);
    bankrollBox.setOutlineColor(sf::Color(90, 210, 255));

    bankrollInputText.setFillColor(sf::Color::White);
    bankrollInputText.setPosition({ 360.f, 255.f });

    bankrollHintText.setFillColor(sf::Color(180, 180, 180));
    bankrollHintText.setPosition({ 340.f, 315.f });

    errorText.setFillColor(sf::Color(255, 120, 120));
    errorText.setPosition({ 340.f, 345.f });

    startButton.setSize({ 300.f, 80.f });
    startButton.setPosition({ 350.f, 405.f });
    startButton.setFillColor(sf::Color(60, 60, 180));

    exitButton.setSize({ 300.f, 80.f });
    exitButton.setPosition({ 350.f, 525.f });
    exitButton.setFillColor(sf::Color(170, 50, 50));

    startText.setFillColor(sf::Color::White);
    exitText.setFillColor(sf::Color::White);

    centerTextInButton(startText, startButton);
    centerTextInButton(exitText, exitButton);

    refreshBankrollText();
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

void MainMenu::refreshBankrollText()
{
    if (bankrollInput.empty())
    {
        bankrollInputText.setString("$");
    }
    else
    {
        bankrollInputText.setString("$" + bankrollInput);
    }

    if (hasValidBankroll())
    {
        errorText.setString("");
    }
    else
    {
        errorText.setString("Please enter a bankroll greater than 0.");
    }
}

void MainMenu::handleTextEntered(unsigned int unicode)
{
    if (unicode >= '0' && unicode <= '9')
    {
        if (bankrollInput.size() < 7)
        {
            bankrollInput += static_cast<char>(unicode);
        }
    }

    refreshBankrollText();
}

void MainMenu::handleBackspace()
{
    if (!bankrollInput.empty())
    {
        bankrollInput.pop_back();
    }

    refreshBankrollText();
}

bool MainMenu::hasValidBankroll() const
{
    if (bankrollInput.empty())
    {
        return false;
    }

    try
    {
        return std::stod(bankrollInput) > 0.0;
    }
    catch (...)
    {
        return false;
    }
}

double MainMenu::getEnteredBankroll() const
{
    if (!hasValidBankroll())
    {
        return 1000.0;
    }

    return std::stod(bankrollInput);
}

void MainMenu::handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame)
{
    if (startButton.getGlobalBounds().contains(mousePos))
    {
        if (hasValidBankroll())
        {
            startGame = true;
        }
        else
        {
            startGame = false;
        }
    }
    else if (exitButton.getGlobalBounds().contains(mousePos))
    {
        exitGame = true;
    }

    refreshBankrollText();
}

void MainMenu::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(0, 85, 20));
    window.draw(background);

    window.draw(titleText);
    window.draw(bankrollLabelText);
    window.draw(bankrollBox);
    window.draw(bankrollInputText);
    window.draw(bankrollHintText);
    window.draw(errorText);

    if (hasValidBankroll())
    {
        startButton.setFillColor(sf::Color(60, 60, 180));
    }
    else
    {
        startButton.setFillColor(sf::Color(70, 70, 100));
    }

    window.draw(startButton);
    window.draw(exitButton);
    window.draw(startText);
    window.draw(exitText);
}