#include "SlotsUI.h"
#include <string>

SlotsUI::SlotsUI(sf::Font& sharedFont)
    : game(1000.0),
    font(sharedFont),
    titleText(font, "SLOTS", 54),
    bankrollText(font, "", 28),
    betText(font, "", 28),
    jackpotText(font, "", 28),
    resultText(font, "", 26),
    payoutText(font, "", 24),
    backText(font, "BACK TO MENU", 20),
    spinText(font, "SPIN", 20),
    hasSpun(false),
    currentBet(50.0),
    betInput("50"),
    enteringBet(false),
    lastPayout(0.0),
    betInputLabelText(font, "Enter Bet Amount", 24),
    betInputText(font, "", 28),
    betHintText(font, "Enter bet and confirm", 18),
    betErrorText(font, "", 18),
    betConfirmText(font, "CONFIRM", 20),
    betCancelText(font, "CANCEL", 20),
    sessionStats(nullptr),
    lastRecordedSpinNumber(0)
{
    loadTextures();

    titleText.setFillColor(sf::Color(210, 120, 255));
    titleText.setPosition({ 400.f, 40.f });

    bankrollText.setFillColor(sf::Color::White);
    bankrollText.setPosition({ 20.f, 20.f });

    betText.setFillColor(sf::Color::White);
    betText.setPosition({ 20.f, 55.f });

    jackpotText.setFillColor(sf::Color::White);
    jackpotText.setPosition({ 580.f, 55.f });

    resultText.setFillColor(sf::Color(230, 230, 255));
    resultText.setPosition({ 0.f, 500.f });

    payoutText.setFillColor(sf::Color::Yellow);
    payoutText.setPosition({ 0.f, 545.f });

    spinButton.setSize({ 180.f, 50.f });
    spinButton.setPosition({ 595.f, 660.f });

    backButton.setSize({ 180.f, 50.f });
    backButton.setPosition({ 785.f, 660.f });

    spinText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);

    centerTextInButton(spinText, spinButton);
    centerTextInButton(backText, backButton);

    overlay.setSize({ 1000.f, 760.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    popupPanel.setSize({ 470.f, 290.f });
    popupPanel.setPosition({ 265.f, 190.f });
    popupPanel.setFillColor(sf::Color(12, 28, 55));
    popupPanel.setOutlineThickness(3.f);
    popupPanel.setOutlineColor(sf::Color(210, 120, 255));

    betInputLabelText.setFillColor(sf::Color(210, 120, 255));
    sf::FloatRect labelBounds = betInputLabelText.getLocalBounds();
    betInputLabelText.setPosition({
        500.f - labelBounds.size.x / 2.f - labelBounds.position.x,
        225.f
    });

    betBox.setSize({ 320.f, 58.f });
    betBox.setPosition({ 340.f, 275.f });
    betBox.setFillColor(sf::Color(20, 20, 60));
    betBox.setOutlineThickness(2.f);
    betBox.setOutlineColor(sf::Color(210, 120, 255));

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
    betConfirmButton.setOutlineColor(sf::Color(210, 120, 255));

    betCancelButton.setSize({ 160.f, 52.f });
    betCancelButton.setPosition({ 520.f, 410.f });
    betCancelButton.setFillColor(sf::Color(180, 65, 85));
    betCancelButton.setOutlineThickness(2.f);
    betCancelButton.setOutlineColor(sf::Color(210, 120, 255));

    betConfirmText.setFillColor(sf::Color::White);
    betCancelText.setFillColor(sf::Color::White);

    centerTextInButton(betConfirmText, betConfirmButton);
    centerTextInButton(betCancelText, betCancelButton);

    updateText();
}

void SlotsUI::loadTextures()
{
    (void)symbolTextures['B'].loadFromFile("assets/images/slots/bar.png");
    (void)symbolTextures['7'].loadFromFile("assets/images/slots/seven.png");
    (void)symbolTextures['J'].loadFromFile("assets/images/slots/letter-j.png");
    (void)symbolTextures['Q'].loadFromFile("assets/images/slots/Q.png");
    (void)symbolTextures['S'].loadFromFile("assets/images/slots/star.png");
    (void)symbolTextures['A'].loadFromFile("assets/images/slots/alien.png");
    (void)symbolTextures['M'].loadFromFile("assets/images/slots/full-moon.png");
    (void)symbolTextures['R'].loadFromFile("assets/images/slots/rocket.png");
    (void)symbolTextures['G'].loadFromFile("assets/images/slots/galaxy.png");
    (void)symbolTextures['2'].loadFromFile("assets/images/slots/2x.png");
    (void)symbolTextures['5'].loadFromFile("assets/images/slots/5x.png");
}

void SlotsUI::refreshBetInputDisplay()
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
        betConfirmButton.setFillColor(sf::Color(125, 45, 180));
    }
    else
    {
        betConfirmButton.setFillColor(sf::Color(70, 70, 100));
    }
}

void SlotsUI::setStartingBankroll(double bankroll)
{
    game = Slots(bankroll);
    hasSpun = false;
    currentBet = 50.0;
    betInput = "50";
    enteringBet = false;
    lastPayout = 0.0;
    lastRecordedSpinNumber = 0;
    updateText();
}

double SlotsUI::getCurrentBankroll() const
{
    return game.getBankroll();
}

void SlotsUI::setSessionStats(SessionStats* stats)
{
    sessionStats = stats;
}

void SlotsUI::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f pos = button.getPosition();
    sf::Vector2f size = button.getSize();

    text.setPosition({
        pos.x + (size.x - bounds.size.x) / 2.f - bounds.position.x,
        pos.y + (size.y - bounds.size.y) / 2.f - bounds.position.y
        });
}

std::string SlotsUI::symbolToString(char c) const
{
    switch (c)
    {
    case 'B': return "BAR";
    case '7': return "7";
    case 'J': return "J";
    case 'Q': return "Q";
    case 'S': return "STAR";
    case 'A': return "ALIEN";
    case 'M': return "MOON";
    case 'R': return "ROCKET";
    case 'G': return "GALAXY";
    case '2': return "2X";
    case '5': return "5X";
    default:  return "?";
    }
}

void SlotsUI::updateText()
{
    bankrollText.setString("Bankroll: $" + std::to_string(static_cast<int>(game.getBankroll())));
    betText.setString("Current Bet: $" + std::to_string(static_cast<int>(currentBet)));
    jackpotText.setString("Jackpot: $" + std::to_string(static_cast<int>(game.displayProgressiveJackpot())));

    if (!hasSpun)
    {
        resultText.setString("Click SPIN to play slots");
        payoutText.setString("");
    }
    else
    {
        if (lastPayout > 0.0)
        {
            resultText.setString("Nice spin. You won.");
            payoutText.setString("Payout: $" + std::to_string(static_cast<int>(lastPayout)));
        }
        else
        {
            resultText.setString("No payout this spin.");
            payoutText.setString("Payout: $0");
        }
    }

    sf::FloatRect resultBounds = resultText.getLocalBounds();
    resultText.setPosition({
        500.f - resultBounds.size.x / 2.f - resultBounds.position.x,
        500.f
        });

    sf::FloatRect payoutBounds = payoutText.getLocalBounds();
    payoutText.setPosition({
        500.f - payoutBounds.size.x / 2.f - payoutBounds.position.x,
        545.f
        });
}


void SlotsUI::commitBetInput()
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
            currentBet = static_cast<double>(value);
        }
    }
    catch (...)
    {
    }

    enteringBet = false;
    updateText();
}

void SlotsUI::handleTextEntered(unsigned int unicode)
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

void SlotsUI::handleBackspace()
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

void SlotsUI::handleScreenClick(sf::Vector2f mousePos, bool& backToMenu)
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
        if (sessionStats)
        {
            sessionStats->getBankroll().setBalance(game.getBankroll());
        }
        backToMenu = true;
        return;
    }

    if (spinButton.getGlobalBounds().contains(mousePos))
    {
        if (game.getBankroll() >= currentBet)
        {
            currentWindow = game.reelsSpin(currentBet);
            lastPayout = game.paytable();
            hasSpun = true;
            if (sessionStats)
            {
                SlotsSummary summary = game.statSummary();
                if (summary.spinNumber > lastRecordedSpinNumber)
                {
                    SlotsRoundSummary rs;
                    rs.betAmount = summary.betMade;
                    rs.payoutAmount = summary.payoutAmount;
                    rs.netChange = summary.netChange;
                    rs.wasThreeInARow = (summary.numLowWins > 0 || summary.numHighWins > 0 || summary.numBarOr7 > 0);
                    rs.wasJackpot = (summary.wonJackpot == 'Y');
                    sessionStats->recordSlotsRound(rs);
                    lastRecordedSpinNumber = summary.spinNumber;
                }
            }
            updateText();
        }
    }
}

void SlotsUI::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(18, 0, 40));
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

    sf::RectangleShape topLine({ 880.f, 3.f });
    topLine.setPosition({ 58.f, 130.f });
    topLine.setFillColor(sf::Color(210, 120, 255));
    window.draw(topLine);

    sf::RectangleShape bottomLine({ 880.f, 3.f });
    bottomLine.setPosition({ 58.f, 610.f });
    bottomLine.setFillColor(sf::Color(210, 120, 255));
    window.draw(bottomLine);

    window.draw(titleText);
    window.draw(bankrollText);
    window.draw(betText);
    window.draw(jackpotText);

    sf::RectangleShape machineBody({ 520.f, 300.f });
    machineBody.setPosition({ 240.f, 180.f });
    machineBody.setFillColor(sf::Color(45, 35, 75));
    machineBody.setOutlineThickness(3.f);
    machineBody.setOutlineColor(sf::Color(210, 120, 255));
    window.draw(machineBody);

    const float startX = 290.f;
    const float startY = 210.f;
    const float cellW = 130.f;
    const float cellH = 80.f;

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            sf::RectangleShape cell({ cellW - 10.f, cellH - 10.f });
            cell.setPosition({
                startX + col * cellW,
                startY + row * cellH
                });
            cell.setFillColor(sf::Color(20, 20, 35));
            cell.setOutlineThickness(2.f);
            cell.setOutlineColor(sf::Color(110, 80, 160));
            window.draw(cell);

            if (hasSpun)
            {
                char symbolChar = currentWindow.getDisplay(col, row);
                if (symbolTextures.find(symbolChar) != symbolTextures.end())
                {
                    sf::Sprite sprite(symbolTextures[symbolChar]);
                    sf::FloatRect bounds = sprite.getLocalBounds();
                    
                    // scale to fit nicely within the cell
                    float scaleX = (cell.getSize().x - 20.f) / bounds.size.x;
                    float scaleY = (cell.getSize().y - 20.f) / bounds.size.y;
                    float scale = std::min(scaleX, scaleY);
                    
                    sprite.setScale({scale, scale});
                    
                    sf::FloatRect scaledBounds = sprite.getGlobalBounds();
                    sprite.setPosition({
                        cell.getPosition().x + (cell.getSize().x - scaledBounds.size.x) / 2.f,
                        cell.getPosition().y + (cell.getSize().y - scaledBounds.size.y) / 2.f
                    });
                    
                    window.draw(sprite);
                }
                else
                {
                    sf::Text symbol(font, symbolToString(symbolChar), 24);
                    symbol.setFillColor(sf::Color::White);

                    sf::FloatRect bounds = symbol.getLocalBounds();
                    symbol.setPosition({
                        cell.getPosition().x + (cell.getSize().x - bounds.size.x) / 2.f - bounds.position.x,
                        cell.getPosition().y + (cell.getSize().y - bounds.size.y) / 2.f - bounds.position.y
                        });

                    window.draw(symbol);
                }
            }
            else
            {
                sf::Text symbol(font, "?", 24);
                symbol.setFillColor(sf::Color::White);

                sf::FloatRect bounds = symbol.getLocalBounds();
                symbol.setPosition({
                    cell.getPosition().x + (cell.getSize().x - bounds.size.x) / 2.f - bounds.position.x,
                    cell.getPosition().y + (cell.getSize().y - bounds.size.y) / 2.f - bounds.position.y
                    });

                window.draw(symbol);
            }
        }
    }

    spinButton.setFillColor(
        (game.getBankroll() >= currentBet)
        ? sf::Color(125, 45, 180)
        : sf::Color(70, 70, 110)
    );

    backButton.setFillColor(sf::Color(180, 65, 85));

    window.draw(spinButton);
    window.draw(backButton);
    window.draw(spinText);
    window.draw(backText);
    window.draw(resultText);
    window.draw(payoutText);

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
