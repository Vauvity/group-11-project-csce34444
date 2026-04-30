#include "RouletteUI.h"
#include <string>

namespace {
    constexpr float TABLE_X = 95.f;
    constexpr float TABLE_Y = 205.f;
    constexpr float CELL_W = 50.f;
    constexpr float CELL_H = 65.f;
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
    clearBetsText(font, "CLEAR BETS", 20),
    placeStraightText(font, "BET", 18),
    currentBet(5.0),
    chipInput("5"),
    enteringChip(false),
    numberInput("0"),
    enteringNumber(false),
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

    betBg.setSize({ 250.f, 40.f });
    betBg.setPosition({ 10.f, 60.f });
    betBg.setFillColor(sf::Color(60, 20, 20, 200));
    betBg.setOutlineThickness(2.f);
    betBg.setOutlineColor(sf::Color(255, 70, 70));

    betText.setFillColor(sf::Color::White);
    betText.setPosition({ 20.f, 65.f });

    selectedBetText.setFillColor(sf::Color(255, 230, 230));
    selectedBetText.setPosition({ 70.f, 155.f });

    numberInputLabelText.setFillColor(sf::Color(255, 230, 230));
    numberInputLabelText.setPosition({ 750.f, 380.f });

    numberBox.setSize({ 80.f, 46.f });
    numberBox.setPosition({ 750.f, 410.f });
    numberBox.setFillColor(sf::Color(28, 10, 18));
    numberBox.setOutlineThickness(2.f);
    numberBox.setOutlineColor(sf::Color(255, 70, 70));

    placeStraightButton.setSize({ 80.f, 46.f });
    placeStraightButton.setPosition({ 840.f, 410.f });

    numberInputText.setFillColor(sf::Color::White);

    resultText.setFillColor(sf::Color::White);
    payoutText.setFillColor(sf::Color(255, 220, 90));

    redButton.setSize({ 125.f, 46.f });
    redButton.setPosition({ 58.f, 605.f });

    blackButton.setSize({ 125.f, 46.f });
    blackButton.setPosition({ 209.f, 605.f });

    evenButton.setSize({ 125.f, 46.f });
    evenButton.setPosition({ 360.f, 605.f });

    oddButton.setSize({ 125.f, 46.f });
    oddButton.setPosition({ 511.f, 605.f });

    lowButton.setSize({ 125.f, 46.f });
    lowButton.setPosition({ 662.f, 605.f });

    highButton.setSize({ 125.f, 46.f });
    highButton.setPosition({ 813.f, 605.f });

    clearBetsButton.setSize({ 180.f, 50.f });
    clearBetsButton.setPosition({ 405.f, 660.f });

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
    clearBetsText.setFillColor(sf::Color::White);
    placeStraightText.setFillColor(sf::Color::White);

    centerTextInButton(redText, redButton);
    centerTextInButton(blackText, blackButton);
    centerTextInButton(evenText, evenButton);
    centerTextInButton(oddText, oddButton);
    centerTextInButton(lowText, lowButton);
    centerTextInButton(highText, highButton);
    centerTextInButton(spinText, spinButton);
    centerTextInButton(backText, backButton);
    centerTextInButton(clearBetsText, clearBetsButton);
    centerTextInButton(placeStraightText, placeStraightButton);

    (void)wheelTexture.loadFromFile("assets/images/roulette/pngimg.com - roulette_PNG50.png");
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



sf::FloatRect RouletteUI::getZeroCellBounds() const
{
    return sf::FloatRect({ 30.f, TABLE_Y }, { 55.f, CELL_H * 3.f });
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
    if (placedChips.empty())
    {
        resultText.setString("Place a bet first.");
        payoutText.setString("");
        updateText();
        return;
    }

    int totalBetAmount = 0;
    for (const auto& c : placedChips) {
        totalBetAmount += c.amount;
    }

    int before = game.getBalance() + totalBetAmount;

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
        summary.betAmount = static_cast<double>(totalBetAmount);
        summary.netChange = static_cast<double>(net);
        summary.payoutAmount = net > 0 ? static_cast<double>(totalBetAmount + net) : 0.0;
        summary.wasStraightUp = false;
        summary.straightUpWon = false;
        sessionStats->recordRouletteRound(summary);
    }

    placedChips.clear();
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

    if (!enteringNumber)
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

    if (!enteringNumber)
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

    if (betBg.getGlobalBounds().contains(mousePos) || betText.getGlobalBounds().contains(mousePos))
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
            sessionStats->getBankroll().setBalance(static_cast<double>(game.getBalance()));
        }
        backToMenu = true;
        return;
    }

    enteringNumber = false;

    auto tryPlaceBet = [&](const RouletteBet& bet, sf::Vector2f pos) {
        if (game.canPlaceBet(static_cast<int>(currentBet))) {
            game.placeBet(bet);
            placedChips.push_back({pos, static_cast<int>(currentBet)});
        } else {
            resultText.setString("Not enough bankroll.");
        }
    };

    int pickedNumber = getClickedTableNumber(mousePos);
    if (pickedNumber != -1)
    {
        sf::FloatRect bounds = (pickedNumber == 0) ? getZeroCellBounds() : getTableCellBounds(pickedNumber);
        tryPlaceBet(RouletteBet(BetType::StraightUp, pickedNumber, static_cast<int>(currentBet)), {bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
        updateText();
        return;
    }

    if (numberBox.getGlobalBounds().contains(mousePos))
    {
        enteringNumber = true;
    }
    else if (placeStraightButton.getGlobalBounds().contains(mousePos))
    {
        int chosenNumber = 0;
        try { chosenNumber = std::stoi(numberInput); } catch (...) { chosenNumber = -1; }
        if (chosenNumber >= 0 && chosenNumber <= 36) {
            sf::FloatRect bounds = (chosenNumber == 0) ? getZeroCellBounds() : getTableCellBounds(chosenNumber);
            tryPlaceBet(RouletteBet(BetType::StraightUp, chosenNumber, static_cast<int>(currentBet)), {bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
        } else {
            resultText.setString("Straight number must be from 0 to 36.");
        }
    }
    else if (redButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(Color::Red, static_cast<int>(currentBet)), {redButton.getPosition().x + redButton.getSize().x / 2.f, redButton.getPosition().y + redButton.getSize().y / 2.f});
    }
    else if (blackButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(Color::Black, static_cast<int>(currentBet)), {blackButton.getPosition().x + blackButton.getSize().x / 2.f, blackButton.getPosition().y + blackButton.getSize().y / 2.f});
    }
    else if (evenButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(BetType::EvenOdd, 0, static_cast<int>(currentBet)), {evenButton.getPosition().x + evenButton.getSize().x / 2.f, evenButton.getPosition().y + evenButton.getSize().y / 2.f});
    }
    else if (oddButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(BetType::EvenOdd, 1, static_cast<int>(currentBet)), {oddButton.getPosition().x + oddButton.getSize().x / 2.f, oddButton.getPosition().y + oddButton.getSize().y / 2.f});
    }
    else if (lowButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(BetType::HighLow, 0, static_cast<int>(currentBet)), {lowButton.getPosition().x + lowButton.getSize().x / 2.f, lowButton.getPosition().y + lowButton.getSize().y / 2.f});
    }
    else if (highButton.getGlobalBounds().contains(mousePos))
    {
        tryPlaceBet(RouletteBet(BetType::HighLow, 1, static_cast<int>(currentBet)), {highButton.getPosition().x + highButton.getSize().x / 2.f, highButton.getPosition().y + highButton.getSize().y / 2.f});
    }
    else if (clearBetsButton.getGlobalBounds().contains(mousePos))
    {
        game.clearBets();
        placedChips.clear();
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
    bottomLine.setPosition({ 58.f, 580.f });
    bottomLine.setFillColor(sf::Color(255, 70, 70));
    window.draw(bottomLine);

    window.draw(betBg);

    window.draw(titleText);
    window.draw(bankrollText);
    window.draw(betText);
    window.draw(selectedBetText);

    sf::Text tableTitle(font, "TABLE", 26);
    tableTitle.setFillColor(sf::Color(255, 230, 230));
    tableTitle.setPosition({ 285.f, 170.f });
    window.draw(tableTitle);

    sf::RectangleShape zeroCell({ 55.f, CELL_H * 3.f });
    zeroCell.setPosition({ 30.f, TABLE_Y });
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
    clearBetsButton.setFillColor(sf::Color(180, 80, 40));
    placeStraightButton.setFillColor(sf::Color(220, 50, 50));

    window.draw(redButton);
    window.draw(blackButton);
    window.draw(evenButton);
    window.draw(oddButton);
    window.draw(lowButton);
    window.draw(highButton);
    window.draw(clearBetsButton);
    window.draw(placeStraightButton);
    window.draw(spinButton);
    window.draw(backButton);

    window.draw(redText);
    window.draw(blackText);
    window.draw(evenText);
    window.draw(oddText);
    window.draw(lowText);
    window.draw(highText);
    window.draw(clearBetsText);
    window.draw(placeStraightText);
    window.draw(spinText);
    window.draw(backText);
    if (!isBallSpinning)
    {
        window.draw(resultText);
        window.draw(payoutText);
    }
    
    window.draw(wheelSprite);

    for (const auto& chip : placedChips)
    {
        sf::CircleShape chipShape(15.f);
        chipShape.setFillColor(sf::Color(255, 215, 0));
        chipShape.setOutlineThickness(2.f);
        chipShape.setOutlineColor(sf::Color::Black);
        chipShape.setOrigin({ 15.f, 15.f });
        chipShape.setPosition(chip.position);
        window.draw(chipShape);

        sf::Text amt(font, std::to_string(chip.amount), 12);
        amt.setFillColor(sf::Color::Black);
        sf::FloatRect ab = amt.getLocalBounds();
        amt.setPosition({
            chip.position.x - ab.size.x / 2.f - ab.position.x,
            chip.position.y - ab.size.y / 2.f - ab.position.y
        });
        window.draw(amt);
    }

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
