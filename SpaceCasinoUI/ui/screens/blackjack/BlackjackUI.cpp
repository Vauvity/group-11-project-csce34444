#include "BlackjackUI.h"
#include <string>
#include <vector>

BlackjackUI::BlackjackUI(sf::Font& sharedFont)
    : game(1000.0),
    font(sharedFont),
    titleText(font, "BLACKJACK", 54),
    bankrollText(font, "", 28),
    betText(font, "", 28),
    dealerText(font, "", 24),
    playerText(font, "", 24),
    messageText(font, "", 24),
    statsText(font, "", 24),
    hitText(font, "HIT", 20),
    standText(font, "STAND", 20),
    doubleText(font, "DOUBLE", 20),
    newRoundText(font, "NEW ROUND", 20),
    backText(font, "BACK TO MENU", 20),
    currentBet(50.0f),
    betInput("50"),
    enteringBet(false),
    betInputLabelText(font, "Enter Bet Amount", 24),
    betInputText(font, "", 28),
    betHintText(font, "Enter bet and confirm", 18),
    betErrorText(font, "", 18),
    betConfirmText(font, "CONFIRM", 20),
    betCancelText(font, "CANCEL", 20),
    roundStarted(false),
    sessionStats(nullptr),
    lastRecordedRoundNumber(0)
{
    titleText.setFillColor(sf::Color(90, 210, 255));
    titleText.setPosition({ 355.f, 40.f });

    bankrollText.setFillColor(sf::Color::White);
    bankrollText.setPosition({ 20.f, 20.f });

    betText.setFillColor(sf::Color::White);
    betText.setPosition({ 20.f, 55.f });

    dealerText.setFillColor(sf::Color(190, 235, 235));
    dealerText.setPosition({ 0.f, 160.f });

    messageText.setFillColor(sf::Color(190, 235, 235));
    messageText.setPosition({ 0.f, 320.f });

    playerText.setFillColor(sf::Color(190, 235, 235));
    playerText.setPosition({ 0.f, 445.f });

    statsText.setFillColor(sf::Color::Yellow);
    statsText.setPosition({ 0.f, 0.f });

    overlay.setSize({ 1000.f, 760.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    popupPanel.setSize({ 470.f, 290.f });
    popupPanel.setPosition({ 265.f, 190.f });
    popupPanel.setFillColor(sf::Color(12, 28, 55));
    popupPanel.setOutlineThickness(3.f);
    popupPanel.setOutlineColor(sf::Color(90, 210, 255));

    betInputLabelText.setFillColor(sf::Color(90, 210, 255));
    sf::FloatRect labelBounds = betInputLabelText.getLocalBounds();
    betInputLabelText.setPosition({
        500.f - labelBounds.size.x / 2.f - labelBounds.position.x,
        225.f
    });

    betBox.setSize({ 320.f, 58.f });
    betBox.setPosition({ 340.f, 275.f });
    betBox.setFillColor(sf::Color(20, 20, 60));
    betBox.setOutlineThickness(2.f);
    betBox.setOutlineColor(sf::Color(90, 210, 255));

    betInputText.setFillColor(sf::Color::White);
    betInputText.setPosition({ 360.f, 285.f });

    betHintText.setFillColor(sf::Color(200, 200, 200));
    betHintText.setPosition({ 340.f, 345.f });

    betErrorText.setFillColor(sf::Color(255, 140, 140));
    betErrorText.setPosition({ 340.f, 372.f });

    betConfirmButton.setSize({ 160.f, 52.f });
    betConfirmButton.setPosition({ 340.f, 410.f });
    betConfirmButton.setFillColor(sf::Color(70, 70, 100));
    betConfirmButton.setOutlineThickness(2.f);
    betConfirmButton.setOutlineColor(sf::Color(90, 210, 255));

    betCancelButton.setSize({ 160.f, 52.f });
    betCancelButton.setPosition({ 520.f, 410.f });
    betCancelButton.setFillColor(sf::Color(180, 65, 85));
    betCancelButton.setOutlineThickness(2.f);
    betCancelButton.setOutlineColor(sf::Color(90, 210, 255));

    betConfirmText.setFillColor(sf::Color::White);
    betCancelText.setFillColor(sf::Color::White);

    setupButtons();

    centerTextInButton(betConfirmText, betConfirmButton);
    centerTextInButton(betCancelText, betCancelButton);

    updateText();
}

void BlackjackUI::refreshBetInputDisplay()
{
    if (betInput.empty())
    {
        betInputText.setString("$");
    }
    else
    {
        betInputText.setString("$" + betInput);
    }

    if (betInput == "0")
    {
        betErrorText.setString("Bet must be greater than 0.");
    }
    else
    {
        betErrorText.setString("");
    }

    if (!betInput.empty() && betInput != "0")
    {
        betConfirmButton.setFillColor(sf::Color(50, 115, 230));
    }
    else
    {
        betConfirmButton.setFillColor(sf::Color(70, 70, 100));
    }
}

void BlackjackUI::setStartingBankroll(double bankroll)
{
    game = BlackjackGame(bankroll);
    currentBet = 50.0f;
    betInput = "50";
    enteringBet = false;
    roundStarted = false;
    lastRecordedRoundNumber = 0;
    updateText();
}

double BlackjackUI::getCurrentBankroll() const
{
    return game.getTableBalance();
}

void BlackjackUI::setSessionStats(SessionStats* stats)
{
    sessionStats = stats;
}

void BlackjackUI::setupButtons()
{
    hitButton.setSize({ 150.f, 50.f });
    hitButton.setPosition({ 55.f, 660.f });

    standButton.setSize({ 150.f, 50.f });
    standButton.setPosition({ 235.f, 660.f });

    doubleButton.setSize({ 150.f, 50.f });
    doubleButton.setPosition({ 415.f, 660.f });

    newRoundButton.setSize({ 180.f, 50.f });
    newRoundButton.setPosition({ 595.f, 660.f });

    backButton.setSize({ 180.f, 50.f });
    backButton.setPosition({ 785.f, 660.f });

    hitText.setFillColor(sf::Color::White);
    standText.setFillColor(sf::Color::White);
    doubleText.setFillColor(sf::Color::White);
    newRoundText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);

    centerTextInButton(hitText, hitButton);
    centerTextInButton(standText, standButton);
    centerTextInButton(doubleText, doubleButton);
    centerTextInButton(newRoundText, newRoundButton);
    centerTextInButton(backText, backButton);
}

void BlackjackUI::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    auto bounds = text.getLocalBounds();
    auto pos = button.getPosition();
    auto size = button.getSize();

    text.setPosition({
        pos.x + (size.x - bounds.size.x) / 2.f - bounds.position.x,
        pos.y + (size.y - bounds.size.y) / 2.f - bounds.position.y
        });
}

std::string BlackjackUI::getDealerDisplay() const
{
    if (!roundStarted)
    {
        return "Dealer\nNo round started";
    }

    if (game.isDealerHoleCardRevealed())
    {
        return "Dealer\n" + game.getDealerHand().toString() +
            "\nValue: " + std::to_string(game.getDealerValue());
    }

    std::vector<Card> cards = game.getDealerHand().getCards();

    if (cards.empty())
    {
        return "Dealer\nNo cards";
    }

    if (cards.size() == 1)
    {
        return "Dealer\n" + cards[0].toString();
    }

    return "Dealer\n" + cards[0].toString() + "  ??";
}

std::string BlackjackUI::getPlayerDisplay() const
{
    if (!roundStarted)
    {
        return "Player\nNo round started";
    }

    if (game.getHandCount() <= 1)
    {
        return "Player\n" + game.getPlayerHand().toString() +
            "\nValue: " + std::to_string(game.getPlayerHand().getValue()) +
            "\nBet: $" + std::to_string(static_cast<int>(currentBet));
    }

    std::string out = "Player Hands\n";

    for (int i = 0; i < game.getHandCount(); ++i)
    {
        out += "Hand " + std::to_string(i + 1);

        if (!game.isRoundOver() && i == game.getActiveHandIndex())
        {
            out += " [ACTIVE]";
        }

        out += "\n";
        out += game.getPlayerHand(i).toString();
        out += "\nValue: " + std::to_string(game.getPlayerHand(i).getValue());

        if (i < game.getHandCount() - 1)
        {
            out += "\n\n";
        }
    }

    out += "\nBet: $" + std::to_string(static_cast<int>(currentBet));
    return out;
}

std::string BlackjackUI::shortenResultText(const std::string& text) const
{
    if (text.find("Dealer Bust") != std::string::npos || text.find("Dealer bust") != std::string::npos)
    {
        return "Dealer busts. You win.";
    }

    if (text.find("Player Bust") != std::string::npos || text.find("Player bust") != std::string::npos)
    {
        return "Player busts. Dealer wins.";
    }

    if (text.find("Push") != std::string::npos || text.find("Tie") != std::string::npos)
    {
        return "Push.";
    }

    if (text.find("Blackjack") != std::string::npos)
    {
        return "Blackjack. You win.";
    }

    if (text.find("Player Win") != std::string::npos)
    {
        return "You win.";
    }

    if (text.find("Dealer Win") != std::string::npos)
    {
        return "Dealer wins.";
    }

    return text;
}

std::string BlackjackUI::getPostRoundStats() const
{
    if (!roundStarted || !game.isRoundOver())
    {
        return "";
    }

    BlackjackRoundSummary summary = game.getRoundSummary();

    std::string text;
    text += "Starting Bankroll: $" + std::to_string(static_cast<int>(summary.startingBankroll)) + "\n";
    text += "Ending Bankroll: $" + std::to_string(static_cast<int>(summary.endingBankroll)) + "\n";
    text += "Net Change: $" + std::to_string(static_cast<int>(summary.netChange)) + "\n";
    text += "Result: " + shortenResultText(game.getRoundResultText());

    return text;
}

std::string BlackjackUI::getStatusMessage() const
{
    if (!roundStarted)
    {
        return "Choose action: Click NEW ROUND to begin blackjack";
    }

    if (game.isRoundOver())
    {
        return shortenResultText(game.getRoundResultText());
    }

    std::string actions = "Choose action: ";
    bool first = true;

    if (game.canHit())
    {
        actions += "Hit";
        first = false;
    }

    if (game.canStand())
    {
        if (!first)
        {
            actions += ", ";
        }
        actions += "Stand";
        first = false;
    }

    if (game.canDoubleDown())
    {
        if (!first)
        {
            actions += ", ";
        }
        actions += "Double Down";
        first = false;
    }

    if (game.canSplit())
    {
        if (!first)
        {
            actions += ", ";
        }
        actions += "Split";
    }

    return actions;
}

void BlackjackUI::updateText()
{
    bankrollText.setString("Bankroll: $" + std::to_string(static_cast<int>(game.getTableBalance())));
    betText.setString("Current Bet: $" + std::to_string(static_cast<int>(currentBet)) + "  (click to change)");

    dealerText.setString(getDealerDisplay());
    messageText.setString(getStatusMessage());
    playerText.setString(getPlayerDisplay());
    statsText.setString(getPostRoundStats());

    auto dealerBounds = dealerText.getLocalBounds();
    dealerText.setPosition({
        500.f - dealerBounds.size.x / 2.f - dealerBounds.position.x,
        160.f
        });

    auto messageBounds = messageText.getLocalBounds();
    messageText.setPosition({
        500.f - messageBounds.size.x / 2.f - messageBounds.position.x,
        320.f
        });

    auto playerBounds = playerText.getLocalBounds();
    playerText.setPosition({
        500.f - playerBounds.size.x / 2.f - playerBounds.position.x,
        445.f
        });
}


void BlackjackUI::commitBetInput()
{
    if (betInput.empty() || betInput == "0")
    {
        betErrorText.setString("Enter a valid bet amount.");
        return;
    }

    try
    {
        int value = std::stoi(betInput);
        if (value > 0)
        {
            currentBet = static_cast<float>(value);
        }
    }
    catch (...)
    {
    }

    enteringBet = false;
    updateText();
}

void BlackjackUI::handleTextEntered(unsigned int unicode)
{
    if (!enteringBet)
    {
        return;
    }

    if (unicode >= '0' && unicode <= '9')
    {
        if (betInput.size() < 6)
        {
            if (betInput == "0")
            {
                betInput.clear();
            }
            betInput += static_cast<char>(unicode);
            refreshBetInputDisplay();
        }
    }
}

void BlackjackUI::handleBackspace()
{
    if (!enteringBet)
    {
        return;
    }

    if (!betInput.empty())
    {
        betInput.pop_back();
        refreshBetInputDisplay();
    }
}

void BlackjackUI::handleGameClick(sf::Vector2f mousePos)
{
    if (hitButton.getGlobalBounds().contains(mousePos))
    {
        if (roundStarted && !game.isRoundOver() && game.canHit())
        {
            game.playerHit();
        }
    }

    if (standButton.getGlobalBounds().contains(mousePos))
    {
        if (roundStarted && !game.isRoundOver() && game.canStand())
        {
            game.playerStand();
        }
    }

    if (doubleButton.getGlobalBounds().contains(mousePos))
    {
        if (roundStarted && !game.isRoundOver() && game.canDoubleDown())
        {
            game.playerDoubleDown();
        }
    }

    if (newRoundButton.getGlobalBounds().contains(mousePos))
    {
        if (!roundStarted || game.isRoundOver())
        {
            if (game.startNewRound(currentBet))
            {
                roundStarted = true;
            }
        }
    }

    updateText();
}

void BlackjackUI::recordRoundIfNeeded()
{
    if (!sessionStats || !roundStarted || !game.isRoundOver())
    {
        return;
    }

    BlackjackRoundSummary summary = game.getRoundSummary();
    if (summary.roundNumber > lastRecordedRoundNumber)
    {
        sessionStats->recordBlackjackRound(summary);
        lastRecordedRoundNumber = summary.roundNumber;
    }
}

void BlackjackUI::handleScreenClick(sf::Vector2f mousePos, bool& backToMenu)
{
    backToMenu = false;

    if (enteringBet)
    {
        if (betConfirmButton.getGlobalBounds().contains(mousePos))
        {
            commitBetInput();
        }
        else if (betCancelButton.getGlobalBounds().contains(mousePos))
        {
            enteringBet = false;
            updateText();
        }
        return;
    }

    if (betText.getGlobalBounds().contains(mousePos))
    {
        enteringBet = true;
        betInput = std::to_string(static_cast<int>(currentBet));
        refreshBetInputDisplay();
        return;
    }

    if (backButton.getGlobalBounds().contains(mousePos))
    {
        recordRoundIfNeeded();
        if (sessionStats)
        {
            sessionStats->syncCurrentBalance(game.getTableBalance());
        }
        roundStarted = false;
        updateText();
        backToMenu = true;
        return;
    }

    handleGameClick(mousePos);
}

void BlackjackUI::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(0, 0, 40));
    window.draw(background);

    for (int i = 0; i < 70; ++i)
    {
        sf::CircleShape star(1.2f);
        star.setFillColor(sf::Color(235, 235, 255));
        star.setPosition({
            static_cast<float>((i * 137) % 980),
            static_cast<float>((i * 83) % 740)
            });
        window.draw(star);
    }

    sf::RectangleShape line1({ 880.f, 3.f });
    line1.setPosition({ 58.f, 130.f });
    line1.setFillColor(sf::Color(90, 210, 255));
    window.draw(line1);

    auto playerBounds = playerText.getGlobalBounds();

    sf::RectangleShape line2({ 880.f, 3.f });
    line2.setPosition({ 58.f, playerBounds.position.y + playerBounds.size.y + 20.f });
    line2.setFillColor(sf::Color(90, 210, 255));
    window.draw(line2);

    window.draw(titleText);
    window.draw(bankrollText);
    window.draw(betText);

    if (roundStarted && game.isRoundOver())
    {
        auto drawCenteredYellowLine = [&](const std::string& text, float y, unsigned int size)
            {
                sf::Text line(font, text, size);
                line.setFillColor(sf::Color::Yellow);

                auto bounds = line.getLocalBounds();
                line.setPosition({
                    500.f - bounds.size.x / 2.f - bounds.position.x,
                    y
                    });

                window.draw(line);
            };

        float y = 150.f;

        drawCenteredYellowLine(
            "Dealer: " + game.getDealerHand().toString() +
            " (" + std::to_string(game.getDealerValue()) + ")",
            y,
            26
        );
        y += 50.f;

        drawCenteredYellowLine("Player Hands:", y, 26);
        y += 36.f;

        drawCenteredYellowLine(
            game.getPlayerHand().toString() +
            " (" + std::to_string(game.getPlayerHand().getValue()) + ")",
            y,
            26
        );
        y += 50.f;

        drawCenteredYellowLine("Results:", y, 26);
        y += 36.f;

        drawCenteredYellowLine(shortenResultText(game.getRoundResultText()), y, 26);
        y += 50.f;

        drawCenteredYellowLine("Round Insight:", y, 26);
        y += 36.f;

        drawCenteredYellowLine("You played that hand well.", y, 26);
        y += 50.f;

        drawCenteredYellowLine("Post Round Stats", y, 26);
        y += 36.f;

        drawCenteredYellowLine(
            "Bankroll: $" + std::to_string(static_cast<int>(game.getTableBalance())),
            y,
            26
        );
        y += 36.f;

        drawCenteredYellowLine(
            "Bet: $" + std::to_string(static_cast<int>(currentBet)),
            y,
            26
        );
    }
    else
    {
        dealerText.setFillColor(sf::Color(190, 235, 235));
        messageText.setFillColor(sf::Color(190, 235, 235));
        playerText.setFillColor(sf::Color(190, 235, 235));

        window.draw(dealerText);
        window.draw(messageText);
        window.draw(playerText);
    }

    hitButton.setFillColor(
        (roundStarted && !game.isRoundOver() && game.canHit())
        ? sf::Color(50, 115, 230)
        : sf::Color(70, 70, 110)
    );

    standButton.setFillColor(
        (roundStarted && !game.isRoundOver() && game.canStand())
        ? sf::Color(50, 115, 230)
        : sf::Color(70, 70, 110)
    );

    doubleButton.setFillColor(
        (roundStarted && !game.isRoundOver() && game.canDoubleDown())
        ? sf::Color(50, 115, 230)
        : sf::Color(70, 70, 110)
    );

    newRoundButton.setFillColor(
        (!roundStarted || game.isRoundOver())
        ? sf::Color(50, 115, 230)
        : sf::Color(70, 70, 110)
    );

    backButton.setFillColor(sf::Color(180, 65, 85));

    window.draw(hitButton);
    window.draw(standButton);
    window.draw(doubleButton);
    window.draw(newRoundButton);
    window.draw(backButton);

    window.draw(hitText);
    window.draw(standText);
    window.draw(doubleText);
    window.draw(newRoundText);
    window.draw(backText);

    if (enteringBet)
    {
        window.draw(overlay);
        window.draw(popupPanel);
        window.draw(betInputLabelText);
        window.draw(betBox);
        window.draw(betInputText);
        window.draw(betHintText);
        window.draw(betErrorText);
        window.draw(betConfirmButton);
        window.draw(betCancelButton);
        window.draw(betConfirmText);
        window.draw(betCancelText);
    }
}