#include "RouletteUI.h"
#include <string>

namespace {
    constexpr float TABLE_X = 95.f;
    constexpr float TABLE_Y = 205.f;
    constexpr float CELL_W = 48.f;
    constexpr float CELL_H = 42.f;
}

RouletteUI::RouletteUI(sf::Font& sharedFont)
    : game(1000),
    font(sharedFont),
    titleText(font, "ROULETTE", 54),
    bankrollText(font, "", 28),
    betText(font, "", 28),
    selectedBetText(font, "", 22),
    numberInputLabelText(font, "Straight Number:", 22),
    numberInputText(font, "", 24),
    resultText(font, "", 24),
    payoutText(font, "", 24),
    spinText(font, "SPIN", 20),
    backText(font, "BACK TO MENU", 20),
    redText(font, "RED", 18),
    blackText(font, "BLACK", 18),
    evenText(font, "EVEN", 18),
    oddText(font, "ODD", 18),
    lowText(font, "1 TO 18", 18),
    highText(font, "19 TO 36", 18),
    straightText(font, "STRAIGHT", 18),
    currentBet(5.0),
    chipInput("5"),
    enteringChip(false),
    numberInput("0"),
    enteringNumber(false),
    selectedBet(SelectedBet::Red),
    chipInputLabelText(font, "Enter Chip Value", 24),
    chipInputText(font, "", 28),
    chipHintText(font, "Enter chip value and confirm", 18),
    chipErrorText(font, "", 18),
    chipConfirmText(font, "CONFIRM", 20),
    chipCancelText(font, "CANCEL", 20),
    hasSpun(false),
    sessionStats(nullptr),
    wheelSprite(wheelTexture),
    isBallSpinning(false),
    ballAngle(0.f)
{
    titleText.setFillColor(sf::Color(255, 85, 85));
    titleText.setPosition({ 355.f, 35.f });

    bankrollText.setFillColor(sf::Color::White);
    bankrollText.setPosition({ 20.f, 20.f });

    betText.setFillColor(sf::Color::White);
    betText.setPosition({ 20.f, 55.f });

    selectedBetText.setFillColor(sf::Color(255, 230, 230));
    selectedBetText.setPosition({ 70.f, 155.f });

    numberInputLabelText.setFillColor(sf::Color(255, 230, 230));
    numberInputLabelText.setPosition({ 760.f, 370.f });

    numberBox.setSize({ 120.f, 46.f });
    numberBox.setPosition({ 795.f, 405.f });
    numberBox.setFillColor(sf::Color(28, 10, 18));
    numberBox.setOutlineThickness(2.f);
    numberBox.setOutlineColor(sf::Color(255, 70, 70));

    numberInputText.setFillColor(sf::Color::White);

    resultText.setFillColor(sf::Color::White);
    payoutText.setFillColor(sf::Color(255, 220, 90));

    redButton.setSize({ 125.f, 46.f });
    redButton.setPosition({ 95.f, 345.f });

    blackButton.setSize({ 125.f, 46.f });
    blackButton.setPosition({ 235.f, 345.f });

    evenButton.setSize({ 125.f, 46.f });
    evenButton.setPosition({ 375.f, 345.f });

    oddButton.setSize({ 125.f, 46.f });
    oddButton.setPosition({ 515.f, 345.f });

    lowButton.setSize({ 125.f, 46.f });
    lowButton.setPosition({ 95.f, 405.f });

    highButton.setSize({ 125.f, 46.f });
    highButton.setPosition({ 235.f, 405.f });

    straightButton.setSize({ 125.f, 46.f });
    straightButton.setPosition({ 375.f, 405.f });

    spinButton.setSize({ 180.f, 50.f });
    spinButton.setPosition({ 595.f, 660.f });

    backButton.setSize({ 180.f, 50.f });
    backButton.setPosition({ 785.f, 660.f });

    redText.setFillColor(sf::Color::White);
    blackText.setFillColor(sf::Color::White);
    evenText.setFillColor(sf::Color::White);
    oddText.setFillColor(sf::Color::White);
    lowText.setFillColor(sf::Color::White);
    highText.setFillColor(sf::Color::White);
    straightText.setFillColor(sf::Color::White);
    spinText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);

    centerTextInButton(redText, redButton);
    centerTextInButton(blackText, blackButton);
    centerTextInButton(evenText, evenButton);
    centerTextInButton(oddText, oddButton);
    centerTextInButton(lowText, lowButton);
    centerTextInButton(highText, highButton);
    centerTextInButton(straightText, straightButton);
    centerTextInButton(spinText, spinButton);
    centerTextInButton(backText, backButton);

    wheelTexture.loadFromFile("assets/images/roulette/pngimg.com - roulette_PNG50.png");
    wheelSprite.setTexture(wheelTexture, true);
    sf::FloatRect bounds = wheelSprite.getLocalBounds();
    wheelSprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    wheelSprite.setScale({ 220.f / bounds.size.x, 220.f / bounds.size.y });
    wheelSprite.setPosition({ 830.f, 260.f });

    overlay.setSize({ 1000.f, 760.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    popupPanel.setSize({ 470.f, 290.f });
    popupPanel.setPosition({ 265.f, 190.f });
    popupPanel.setFillColor(sf::Color(12, 28, 55));
    popupPanel.setOutlineThickness(3.f);
    popupPanel.setOutlineColor(sf::Color(255, 70, 70));

    chipInputLabelText.setFillColor(sf::Color(255, 70, 70));
    sf::FloatRect labelBounds = chipInputLabelText.getLocalBounds();
    chipInputLabelText.setPosition({
        500.f - labelBounds.size.x / 2.f - labelBounds.position.x,
        225.f
    });

    chipBox.setSize({ 320.f, 58.f });
    chipBox.setPosition({ 340.f, 275.f });
    chipBox.setFillColor(sf::Color(20, 20, 60));
    chipBox.setOutlineThickness(2.f);
    chipBox.setOutlineColor(sf::Color(255, 70, 70));

    chipInputText.setFillColor(sf::Color::White);
    chipInputText.setPosition({ 360.f, 285.f });

    chipHintText.setFillColor(sf::Color(200, 200, 200));
    chipHintText.setPosition({ 340.f, 345.f });

    chipErrorText.setFillColor(sf::Color(255, 140, 140));
    chipErrorText.setPosition({ 340.f, 372.f });

    chipConfirmButton.setSize({ 160.f, 52.f });
    chipConfirmButton.setPosition({ 340.f, 410.f });
    chipConfirmButton.setFillColor(sf::Color(70, 70, 100));
    chipConfirmButton.setOutlineThickness(2.f);
    chipConfirmButton.setOutlineColor(sf::Color(255, 70, 70));

    chipCancelButton.setSize({ 160.f, 52.f });
    chipCancelButton.setPosition({ 520.f, 410.f });
    chipCancelButton.setFillColor(sf::Color(180, 65, 85));
    chipCancelButton.setOutlineThickness(2.f);
    chipCancelButton.setOutlineColor(sf::Color(255, 70, 70));

    chipConfirmText.setFillColor(sf::Color::White);
    chipCancelText.setFillColor(sf::Color::White);

    centerTextInButton(chipConfirmText, chipConfirmButton);
    centerTextInButton(chipCancelText, chipCancelButton);

    updateText();
}

void RouletteUI::refreshChipInputDisplay()
{
    if (chipInput.empty())
    {
        chipInputText.setString("$");
    }
    else
    {
        chipInputText.setString("$" + chipInput);
    }

    if (chipInput == "0")
    {
        chipErrorText.setString("Chip must be greater than 0.");
    }
    else
    {
        chipErrorText.setString("");
    }

    if (!chipInput.empty() && chipInput != "0")
    {
        chipConfirmButton.setFillColor(sf::Color(220, 50, 50));
    }
    else
    {
        chipConfirmButton.setFillColor(sf::Color(70, 70, 100));
    }
}

void RouletteUI::setStartingBankroll(double bankroll)
{
    game = RouletteGame(static_cast<int>(bankroll));
    currentBet = 5.0;
    chipInput = "5";
    enteringChip = false;
    numberInput = "0";
    enteringNumber = false;
    selectedBet = SelectedBet::Red;
    hasSpun = false;
    resultText.setString("");
    payoutText.setString("");
    updateText();
}

double RouletteUI::getCurrentBankroll() const
{
    return static_cast<double>(game.getBalance());
}

void RouletteUI::setSessionStats(SessionStats* stats)
{
    sessionStats = stats;
}

void RouletteUI::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f pos = button.getPosition();
    sf::Vector2f size = button.getSize();

    text.setPosition({
        pos.x + (size.x - bounds.size.x) / 2.f - bounds.position.x,
        pos.y + (size.y - bounds.size.y) / 2.f - bounds.position.y
        });
}

std::string RouletteUI::getSelectedBetLabel() const
{
    switch (selectedBet)
    {
    case SelectedBet::Red: return "Selected Bet: Red";
    case SelectedBet::Black: return "Selected Bet: Black";
    case SelectedBet::Even: return "Selected Bet: Even";
    case SelectedBet::Odd: return "Selected Bet: Odd";
    case SelectedBet::Low: return "Selected Bet: 1 to 18";
    case SelectedBet::High: return "Selected Bet: 19 to 36";
    case SelectedBet::Straight: return "Selected Bet: Straight Up " + numberInput;
    default: return "Selected Bet";
    }
}

sf::FloatRect RouletteUI::getZeroCellBounds() const
{
    return sf::FloatRect({ 35.f, TABLE_Y }, { 45.f, CELL_H * 3.f });
}

sf::FloatRect RouletteUI::getTableCellBounds(int number) const
{
    int n = number - 1;
    int column = n / 3;
    int row = n % 3;
    return sf::FloatRect({ TABLE_X + column * CELL_W, TABLE_Y + row * CELL_H }, { CELL_W, CELL_H });
}

int RouletteUI::getClickedTableNumber(sf::Vector2f mousePos) const
{
    if (getZeroCellBounds().contains(mousePos))
    {
        return 0;
    }

    for (int n = 1; n <= 36; ++n)
    {
        if (getTableCellBounds(n).contains(mousePos))
        {
            return n;
        }
    }

    return -1;
}

bool RouletteUI::isRedNumber(int number) const
{
    int reds[] = { 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };
    for (int r : reds)
    {
        if (r == number)
        {
            return true;
        }
    }
    return false;
}

void RouletteUI::updateText()
{
    bankrollText.setString("Bankroll: $" + std::to_string(game.getBalance()));
    betText.setString("Chip Value: $" + std::to_string(static_cast<int>(currentBet)));
    selectedBetText.setString(getSelectedBetLabel());

    numberInputText.setString(numberInput);

    auto numberBounds = numberInputText.getLocalBounds();
    numberInputText.setPosition({
        numberBox.getPosition().x + (numberBox.getSize().x - numberBounds.size.x) / 2.f - numberBounds.position.x,
        numberBox.getPosition().y + (numberBox.getSize().y - numberBounds.size.y) / 2.f - numberBounds.position.y
        });

    auto resultBounds = resultText.getLocalBounds();
    resultText.setPosition({
        500.f - resultBounds.size.x / 2.f - resultBounds.position.x,
        520.f
        });

    auto payoutBounds = payoutText.getLocalBounds();
    payoutText.setPosition({
        500.f - payoutBounds.size.x / 2.f - payoutBounds.position.x,
        555.f
        });
}


void RouletteUI::commitChipInput()
{
    if (chipInput.empty() || chipInput == "0")
    {
        chipErrorText.setString("Enter a valid chip value.");
        return;
    }

    try
    {
        int value = std::stoi(chipInput);
        if (value > 0)
        {
            currentBet = static_cast<double>(value);
        }
    }
    catch (...)
    {
    }

    enteringChip = false;
    updateText();
}

void RouletteUI::spinRound()
{
    if (!game.canPlaceBet(static_cast<int>(currentBet)))
    {
        resultText.setString("Not enough bankroll for that bet.");
        payoutText.setString("");
        updateText();
        return;
    }

    RouletteBet bet(Color::Red, static_cast<int>(currentBet));

    switch (selectedBet)
    {
    case SelectedBet::Red:
        bet = RouletteBet(Color::Red, static_cast<int>(currentBet));
        break;
    case SelectedBet::Black:
        bet = RouletteBet(Color::Black, static_cast<int>(currentBet));
        break;
    case SelectedBet::Even:
        bet = RouletteBet(BetType::EvenOdd, 0, static_cast<int>(currentBet));
        break;
    case SelectedBet::Odd:
        bet = RouletteBet(BetType::EvenOdd, 1, static_cast<int>(currentBet));
        break;
    case SelectedBet::Low:
        bet = RouletteBet(BetType::HighLow, 0, static_cast<int>(currentBet));
        break;
    case SelectedBet::High:
        bet = RouletteBet(BetType::HighLow, 1, static_cast<int>(currentBet));
        break;
    case SelectedBet::Straight:
    {
        int chosenNumber = 0;
        try
        {
            chosenNumber = std::stoi(numberInput);
        }
        catch (...)
        {
            chosenNumber = 0;
        }

        if (chosenNumber < 0 || chosenNumber > 36)
        {
            resultText.setString("Straight number must be from 0 to 36.");
            payoutText.setString("");
            updateText();
            return;
        }

        bet = RouletteBet(BetType::StraightUp, chosenNumber, static_cast<int>(currentBet));
        break;
    }
    }

    int before = game.getBalance();

    game.placeBet(bet);
    game.spin();
    game.resolve();

    RouletteRoundResult round = game.getLastResult();
    int after = game.getBalance();
    int net = after - before;

    resultText.setString(round.toString());

    if (net > 0)
    {
        payoutText.setString("You won $" + std::to_string(net));
    }
    else if (net < 0)
    {
        payoutText.setString("You lost $" + std::to_string(-net));
    }
    else
    {
        payoutText.setString("Push");
    }

    if (sessionStats)
    {
        RouletteRoundSummary summary{};
        summary.betAmount = currentBet;
        summary.netChange = static_cast<double>(net);
        summary.payoutAmount = net > 0 ? currentBet + net : 0.0;
        summary.wasStraightUp = (selectedBet == SelectedBet::Straight);
        summary.straightUpWon = (selectedBet == SelectedBet::Straight && net > 0);
        sessionStats->recordRouletteRound(summary, static_cast<double>(after));
    }

    hasSpun = true;
    isBallSpinning = true;
    ballAngle = 0.f;
    ballAnimationClock.restart();
    
    updateText();
}

void RouletteUI::handleTextEntered(unsigned int unicode)
{
    if (unicode < '0' || unicode > '9')
    {
        return;
    }

    if (enteringChip)
    {
        if (chipInput.size() < 6)
        {
            if (chipInput == "0")
            {
                chipInput.clear();
            }
            chipInput += static_cast<char>(unicode);
            refreshChipInputDisplay();
        }
        return;
    }

    if (!enteringNumber || selectedBet != SelectedBet::Straight)
    {
        return;
    }

    if (numberInput.size() < 2)
    {
        if (numberInput == "0")
        {
            numberInput = "";
        }
        numberInput += static_cast<char>(unicode);
    }

    updateText();
}

void RouletteUI::handleBackspace()
{
    if (enteringChip)
    {
        if (!chipInput.empty())
        {
            chipInput.pop_back();
        }
        refreshChipInputDisplay();
        return;
    }

    if (!enteringNumber || selectedBet != SelectedBet::Straight)
    {
        return;
    }

    if (!numberInput.empty())
    {
        numberInput.pop_back();
    }

    if (numberInput.empty())
    {
        numberInput = "0";
    }

    updateText();
}

void RouletteUI::handleScreenClick(sf::Vector2f mousePos, bool& backToMenu)
{
    backToMenu = false;

    if (enteringChip)
    {
        if (chipConfirmButton.getGlobalBounds().contains(mousePos))
        {
            commitChipInput();
        }
        else if (chipCancelButton.getGlobalBounds().contains(mousePos))
        {
            enteringChip = false;
            updateText();
        }
        return;
    }

    if (betText.getGlobalBounds().contains(mousePos))
    {
        enteringChip = true;
        enteringNumber = false;
        chipInput = std::to_string(static_cast<int>(currentBet));
        refreshChipInputDisplay();
        return;
    }

    if (backButton.getGlobalBounds().contains(mousePos))
    {
        if (sessionStats)
        {
            sessionStats->syncCurrentBalance(static_cast<double>(game.getBalance()));
        }
        backToMenu = true;
        return;
    }

    enteringNumber = false;

    int pickedNumber = getClickedTableNumber(mousePos);
    if (pickedNumber != -1)
    {
        selectedBet = SelectedBet::Straight;
        numberInput = std::to_string(pickedNumber);
        enteringNumber = true;
        updateText();
        return;
    }

    if (numberBox.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Straight;
        enteringNumber = true;
    }
    else if (redButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Red;
    }
    else if (blackButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Black;
    }
    else if (evenButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Even;
    }
    else if (oddButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Odd;
    }
    else if (lowButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Low;
    }
    else if (highButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::High;
    }
    else if (straightButton.getGlobalBounds().contains(mousePos))
    {
        selectedBet = SelectedBet::Straight;
        enteringNumber = true;
    }
    else if (spinButton.getGlobalBounds().contains(mousePos))
    {
        commitChipInput();
        spinRound();
        return;
    }

    updateText();
}

void RouletteUI::draw(sf::RenderWindow& window)
{
    sf::RectangleShape background({ 1000.f, 760.f });
    background.setFillColor(sf::Color(26, 0, 4));
    window.draw(background);

    for (int i = 0; i < 85; ++i)
    {
        sf::CircleShape star(1.2f);
        star.setFillColor(sf::Color::White);

        float x = static_cast<float>((i * 97) % 1000);
        float y = static_cast<float>((i * 53) % 760);

        if (i % 7 == 0)
        {
            star.setRadius(1.8f);
        }

        star.setPosition({ x, y });
        window.draw(star);
    }

    sf::RectangleShape topLine({ 880.f, 3.f });
    topLine.setPosition({ 58.f, 125.f });
    topLine.setFillColor(sf::Color(255, 70, 70));
    window.draw(topLine);

    sf::RectangleShape bottomLine({ 880.f, 3.f });
    bottomLine.setPosition({ 58.f, 610.f });
    bottomLine.setFillColor(sf::Color(255, 70, 70));
    window.draw(bottomLine);

    window.draw(titleText);
    window.draw(bankrollText);
    window.draw(betText);
    window.draw(selectedBetText);

    sf::Text tableTitle(font, "TABLE", 26);
    tableTitle.setFillColor(sf::Color(255, 230, 230));
    tableTitle.setPosition({ 285.f, 170.f });
    window.draw(tableTitle);

    sf::RectangleShape zeroCell({ 45.f, CELL_H * 3.f });
    zeroCell.setPosition({ 35.f, TABLE_Y });
    zeroCell.setFillColor(sf::Color(20, 120, 50));
    zeroCell.setOutlineThickness(2.f);
    zeroCell.setOutlineColor(sf::Color::White);
    window.draw(zeroCell);

    sf::Text zeroText(font, "0", 22);
    zeroText.setFillColor(sf::Color::White);
    auto zeroBounds = zeroText.getLocalBounds();
    zeroText.setPosition({
        zeroCell.getPosition().x + (zeroCell.getSize().x - zeroBounds.size.x) / 2.f - zeroBounds.position.x,
        zeroCell.getPosition().y + (zeroCell.getSize().y - zeroBounds.size.y) / 2.f - zeroBounds.position.y + 42.f
        });
    window.draw(zeroText);

    for (int n = 1; n <= 36; ++n)
    {
        sf::FloatRect bounds = getTableCellBounds(n);
        sf::RectangleShape cell({ bounds.size.x, bounds.size.y });
        cell.setPosition(bounds.position);
        cell.setFillColor(isRedNumber(n) ? sf::Color(185, 35, 40) : sf::Color(30, 30, 30));
        cell.setOutlineThickness(1.5f);
        cell.setOutlineColor(sf::Color::White);
        window.draw(cell);

        sf::Text numberText(font, std::to_string(n), 16);
        numberText.setFillColor(sf::Color::White);
        auto textBounds = numberText.getLocalBounds();
        numberText.setPosition({
            bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.f - textBounds.position.x,
            bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.f - textBounds.position.y
            });
        window.draw(numberText);
    }


    if (hasSpun && !isBallSpinning)
    {
        RouletteRoundResult round = game.getLastResult();
        sf::Text lastNumber(font, std::to_string(round.number), 46);
        if (round.color == Color::Red)
        {
            lastNumber.setFillColor(sf::Color(185, 35, 40));
        }
        else if (round.color == Color::Black)
        {
            lastNumber.setFillColor(sf::Color::Black);
        }
        else
        {
            lastNumber.setFillColor(sf::Color(20, 120, 50));
        }

        auto lastBounds = lastNumber.getLocalBounds();
        lastNumber.setOutlineThickness(2.f);
        lastNumber.setOutlineColor(sf::Color(255, 255, 255, 150));
        lastNumber.setPosition({
            830.f - lastBounds.size.x / 2.f - lastBounds.position.x,
            260.f - lastBounds.size.y / 2.f - lastBounds.position.y
            });
        window.draw(lastNumber);
    }

    window.draw(numberInputLabelText);
    window.draw(numberBox);
    window.draw(numberInputText);

    redButton.setFillColor(sf::Color(200, 30, 40));
    blackButton.setFillColor(sf::Color(35, 35, 35));
    evenButton.setFillColor(sf::Color(120, 30, 40));
    oddButton.setFillColor(sf::Color(120, 30, 40));
    lowButton.setFillColor(sf::Color(150, 40, 40));
    highButton.setFillColor(sf::Color(150, 40, 40));
    straightButton.setFillColor(sf::Color(200, 90, 40));
    spinButton.setFillColor(sf::Color(220, 50, 50));
    backButton.setFillColor(sf::Color(180, 40, 60));

    window.draw(redButton);
    window.draw(blackButton);
    window.draw(evenButton);
    window.draw(oddButton);
    window.draw(lowButton);
    window.draw(highButton);
    window.draw(straightButton);
    window.draw(spinButton);
    window.draw(backButton);

    window.draw(redText);
    window.draw(blackText);
    window.draw(evenText);
    window.draw(oddText);
    window.draw(lowText);
    window.draw(highText);
    window.draw(straightText);
    window.draw(spinText);
    window.draw(backText);
    if (!isBallSpinning)
    {
        window.draw(resultText);
        window.draw(payoutText);
    }
    
    window.draw(wheelSprite);

    if (isBallSpinning)
    {
        float elapsed = ballAnimationClock.getElapsedTime().asSeconds();
        if (elapsed > 1.5f) 
        {
            isBallSpinning = false;
        }
        else
        {
            ballAngle += 12.f; 
            
            sf::CircleShape ball(6.f);
            ball.setFillColor(sf::Color::White);
            ball.setOrigin({ 6.f, 6.f });
            
            float rad = ballAngle * 3.14159f / 180.f;
            float bx = 830.f + std::cos(rad) * 92.f;
            float by = 260.f + std::sin(rad) * 92.f;
            
            ball.setPosition({ bx, by });
            window.draw(ball);
        }
    }

    if (enteringChip)
    {
        window.draw(overlay);
        window.draw(popupPanel);
        window.draw(chipInputLabelText);
        window.draw(chipBox);
        window.draw(chipInputText);
        window.draw(chipHintText);
        window.draw(chipErrorText);
        window.draw(chipConfirmButton);
        window.draw(chipCancelButton);
        window.draw(chipConfirmText);
        window.draw(chipCancelText);
    }
}
