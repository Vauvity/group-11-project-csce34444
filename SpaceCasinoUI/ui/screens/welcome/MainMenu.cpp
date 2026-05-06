#include "MainMenu.h"
#include <cmath>

MainMenu::MainMenu(sf::Font& sharedFont)
    : font(sharedFont),
    titleText(font, "WELCOME TO SPACE CASINO", 50),
    bankrollLabelText(font, "ENTER STARTING BANKROLL", 24),
    bankrollInputText(font, "", 28),
    bankrollHintText(font, "", 18),
    errorText(font, "", 18),
    startText(font, "START GAME", 22),
    exitText(font, "EXIT", 22),
    confirmText(font, "CONFIRM", 20),
    cancelText(font, "CANCEL", 20),
    settingsText(font, "SETTINGS", 18),
    bankrollInput(""),
    bgSprite(bgTexture),
    settingsPanel({ 500.f, 380.f }),
    settingsTitleText(font, "Audio Settings", 32),
    musicSliderBg({ 200.f, 20.f }),
    blackjackSfxSliderBg({ 200.f, 20.f }),
    rouletteSfxSliderBg({ 200.f, 20.f }),
    slotsSfxSliderBg({ 200.f, 20.f }),
    musicSliderFill({ 0.f, 20.f }),
    blackjackSfxSliderFill({ 0.f, 20.f }),
    rouletteSfxSliderFill({ 0.f, 20.f }),
    slotsSfxSliderFill({ 0.f, 20.f }),
    musicLabelText(font, "Music", 20),
    blackjackSfxLabelText(font, "Blackjack SFX", 20),
    rouletteSfxLabelText(font, "Roulette SFX", 20),
    slotsSfxLabelText(font, "Slots SFX", 20),
    settingsCloseButton({ 180.f, 50.f }),
    settingsCloseText(font, "CLOSE", 20)
{
    titleText.setFillColor(sf::Color(90, 210, 255));
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setPosition({
        500.f - bounds.size.x / 2.f - bounds.position.x,
        95.f
        });

    startButton.setSize({ 260.f, 90.f });
    startButton.setPosition({ 370.f, 250.f });
    startButton.setFillColor(sf::Color(50, 115, 230));
    startButton.setOutlineThickness(2.f);
    startButton.setOutlineColor(sf::Color(90, 210, 255));

    exitButton.setSize({ 260.f, 90.f });
    exitButton.setPosition({ 370.f, 390.f });
    exitButton.setFillColor(sf::Color(180, 65, 85));
    exitButton.setOutlineThickness(2.f);
    exitButton.setOutlineColor(sf::Color(90, 210, 255));

    startText.setFillColor(sf::Color::White);
    exitText.setFillColor(sf::Color::White);

    centerTextInButton(startText, startButton);
    centerTextInButton(exitText, exitButton);
    
    settingsButton.setSize({ 120.f, 40.f });
    settingsButton.setPosition({ 20.f, 700.f });
    settingsButton.setFillColor(sf::Color(50, 50, 60));
    settingsButton.setOutlineThickness(2.f);
    settingsButton.setOutlineColor(sf::Color(200, 200, 200));
    settingsText.setFillColor(sf::Color(200, 200, 200));
    centerTextInButton(settingsText, settingsButton);

    overlay.setSize({ 1000.f, 760.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    popupPanel.setSize({ 470.f, 290.f });
    popupPanel.setPosition({ 265.f, 190.f });
    popupPanel.setFillColor(sf::Color(12, 28, 55));
    popupPanel.setOutlineThickness(3.f);
    popupPanel.setOutlineColor(sf::Color(90, 210, 255));

    bankrollLabelText.setFillColor(sf::Color(90, 210, 255));
    sf::FloatRect labelBounds = bankrollLabelText.getLocalBounds();
    bankrollLabelText.setPosition({
        500.f - labelBounds.size.x / 2.f - labelBounds.position.x,
        225.f
        });

    bankrollBox.setSize({ 320.f, 58.f });
    bankrollBox.setPosition({ 340.f, 275.f });
    bankrollBox.setFillColor(sf::Color(20, 20, 60));
    bankrollBox.setOutlineThickness(2.f);
    bankrollBox.setOutlineColor(sf::Color(90, 210, 255));

    bankrollInputText.setFillColor(sf::Color::White);
    bankrollInputText.setPosition({ 360.f, 285.f });

    bankrollHintText.setFillColor(sf::Color(200, 200, 200));
    bankrollHintText.setPosition({ 340.f, 345.f });

    errorText.setFillColor(sf::Color(255, 140, 140));
    errorText.setPosition({ 340.f, 372.f });

    confirmButton.setSize({ 160.f, 52.f });
    confirmButton.setPosition({ 340.f, 410.f });
    confirmButton.setFillColor(sf::Color(70, 70, 100));
    confirmButton.setOutlineThickness(2.f);
    confirmButton.setOutlineColor(sf::Color(90, 210, 255));

    cancelButton.setSize({ 160.f, 52.f });
    cancelButton.setPosition({ 520.f, 410.f });
    cancelButton.setFillColor(sf::Color(120, 120, 120));
    cancelButton.setOutlineThickness(2.f);
    cancelButton.setOutlineColor(sf::Color(90, 210, 255));

    confirmText.setFillColor(sf::Color::White);
    cancelText.setFillColor(sf::Color::White);

    centerTextInButton(confirmText, confirmButton);
    centerTextInButton(cancelText, cancelButton);

    (void)bgTexture.loadFromFile("assets/images/global/bg_nebula.png");
    bgSprite.setTexture(bgTexture, true);
    sf::FloatRect bgBounds = bgSprite.getLocalBounds();
    if (bgBounds.size.x > 0 && bgBounds.size.y > 0)
    {
        bgSprite.setScale({ 1000.f / bgBounds.size.x, 760.f / bgBounds.size.y });
    }

    refreshBankrollText();

    settingsPanel.setPosition({ 250.f, 190.f });
    settingsPanel.setFillColor(sf::Color(30, 35, 45));
    settingsPanel.setOutlineThickness(2.f);
    settingsPanel.setOutlineColor(sf::Color(255, 210, 90));

    settingsTitleText.setFillColor(sf::Color(255, 210, 90));
    settingsTitleText.setPosition({ 380.f, 210.f });

    musicLabelText.setPosition({ 280.f, 260.f });
    blackjackSfxLabelText.setPosition({ 280.f, 310.f });
    rouletteSfxLabelText.setPosition({ 280.f, 360.f });
    slotsSfxLabelText.setPosition({ 280.f, 410.f });

    musicSliderBg.setPosition({ 480.f, 265.f });
    blackjackSfxSliderBg.setPosition({ 480.f, 315.f });
    rouletteSfxSliderBg.setPosition({ 480.f, 365.f });
    slotsSfxSliderBg.setPosition({ 480.f, 415.f });

    musicSliderFill.setPosition({ 480.f, 265.f });
    blackjackSfxSliderFill.setPosition({ 480.f, 315.f });
    rouletteSfxSliderFill.setPosition({ 480.f, 365.f });
    slotsSfxSliderFill.setPosition({ 480.f, 415.f });

    musicSliderBg.setFillColor(sf::Color(80, 80, 90));
    blackjackSfxSliderBg.setFillColor(sf::Color(80, 80, 90));
    rouletteSfxSliderBg.setFillColor(sf::Color(80, 80, 90));
    slotsSfxSliderBg.setFillColor(sf::Color(80, 80, 90));

    musicSliderFill.setFillColor(sf::Color(50, 115, 230));
    blackjackSfxSliderFill.setFillColor(sf::Color(50, 115, 230));
    rouletteSfxSliderFill.setFillColor(sf::Color(50, 115, 230));
    slotsSfxSliderFill.setFillColor(sf::Color(50, 115, 230));

    musicLabelText.setFillColor(sf::Color::White);
    blackjackSfxLabelText.setFillColor(sf::Color::White);
    rouletteSfxLabelText.setFillColor(sf::Color::White);
    slotsSfxLabelText.setFillColor(sf::Color::White);

    settingsCloseButton.setPosition({ 410.f, 490.f });
    settingsCloseButton.setFillColor(sf::Color(180, 65, 85));
    settingsCloseButton.setOutlineThickness(2.f);
    settingsCloseButton.setOutlineColor(sf::Color(255, 210, 90));

    settingsCloseText.setFillColor(sf::Color::White);
    centerTextInButton(settingsCloseText, settingsCloseButton);
}

void MainMenu::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonPos = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();

    text.setPosition({
        buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.f - textBounds.position.x,
        buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.f - textBounds.position.y - 3.f
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

    if (bankrollInput == "0")
    {
        errorText.setString("Bankroll must be greater than 0.");
    }
    else
    {
        errorText.setString("");
    }

    if (!bankrollInput.empty() && bankrollInput != "0")
    {
        confirmButton.setFillColor(sf::Color(50, 115, 230));
    }
    else
    {
        confirmButton.setFillColor(sf::Color(70, 70, 100));
    }
}

void MainMenu::setAudioSettings(AudioSettings* settings)
{
    audioSettings = settings;
    refreshSettingsDisplay();
}

void MainMenu::refreshSettingsDisplay()
{
    if (!audioSettings) return;

    musicLabelText.setString("Music");
    blackjackSfxLabelText.setString("Blackjack SFX");
    rouletteSfxLabelText.setString("Roulette SFX");
    slotsSfxLabelText.setString("Slots SFX");

    musicSliderFill.setSize({ 200.f * std::sqrt(audioSettings->musicVolume / 100.f), 20.f });
    blackjackSfxSliderFill.setSize({ 200.f * std::sqrt(audioSettings->blackjackSfxVolume / 100.f), 20.f });
    rouletteSfxSliderFill.setSize({ 200.f * std::sqrt(audioSettings->rouletteSfxVolume / 100.f), 20.f });
    slotsSfxSliderFill.setSize({ 200.f * std::sqrt(audioSettings->slotsSfxVolume / 100.f), 20.f });
}

void MainMenu::handleTextEntered(unsigned int unicode)
{
    if (!showingBankrollInput)
    {
        return;
    }

    bankrollHintText.setString("");

    if (unicode >= '0' && unicode <= '9')
    {
        if (bankrollInput.size() < 7)
        {
            bankrollInput += static_cast<char>(unicode);
        }
    }
    else if (unicode >= 32 && unicode <= 126)
    {
        bankrollHintText.setString("Type numbers only.");
    }

    refreshBankrollText();
}

void MainMenu::handleBackspace()
{
    if (!showingBankrollInput)
    {
        return;
    }

    if (!bankrollInput.empty())
    {
        bankrollInput.pop_back();
    }

    bankrollHintText.setString("");
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

void MainMenu::resetSession()
{
    bankrollSetForSession = false;
    showingBankrollInput = false;
    bankrollInput.clear();
    bankrollHintText.setString("");
    errorText.setString("");
    refreshBankrollText();
}

void MainMenu::handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame)
{
    startGame = false;
    exitGame = false;

    if (showingSettingsPopup)
    {
        if (settingsCloseButton.getGlobalBounds().contains(mousePos))
        {
            showingSettingsPopup = false;
        }
        return;
    }

    if (!showingBankrollInput)
    {
        if (settingsButton.getGlobalBounds().contains(mousePos))
        {
            showingSettingsPopup = true;
            refreshSettingsDisplay();
            return;
        }

        if (startButton.getGlobalBounds().contains(mousePos))
        {
            if (bankrollSetForSession)
            {
                startGame = true;
            }
            else
            {
                showingBankrollInput = true;
                bankrollHintText.setString("");
                errorText.setString("");
                refreshBankrollText();
            }
            return;
        }

        if (exitButton.getGlobalBounds().contains(mousePos))
        {
            exitGame = true;
            return;
        }
    }
    else
    {
        if (confirmButton.getGlobalBounds().contains(mousePos))
        {
            if (bankrollInput == "0")
            {
                errorText.setString("Bankroll must be greater than 0.");
                return;
            }

            if (hasValidBankroll())
            {
                bankrollSetForSession = true;
                showingBankrollInput = false;
                bankrollHintText.setString("");
                errorText.setString("");
                startGame = true;
                return;
            }
        }

        if (cancelButton.getGlobalBounds().contains(mousePos))
        {
            showingBankrollInput = false;
            bankrollInput.clear();
            bankrollInputText.setString("$");
            bankrollHintText.setString("");
            errorText.setString("");
            refreshBankrollText();
            return;
        }
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(bgSprite);

    sf::RectangleShape topLine({ 880.f, 3.f });
    topLine.setPosition({ 58.f, 170.f });
    topLine.setFillColor(sf::Color(90, 210, 255));
    window.draw(topLine);

    sf::RectangleShape bottomLine({ 880.f, 3.f });
    bottomLine.setPosition({ 58.f, 610.f });
    bottomLine.setFillColor(sf::Color(90, 210, 255));
    window.draw(bottomLine);

    window.draw(titleText);
    window.draw(startButton);
    window.draw(exitButton);
    window.draw(settingsButton);
    window.draw(startText);
    window.draw(exitText);
    window.draw(settingsText);

    if (showingSettingsPopup)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

            auto updateSlider = [&](sf::RectangleShape& bg, float& volume) {
                sf::FloatRect bounds = bg.getGlobalBounds();
                bounds.position.y -= 10.f; bounds.size.y += 20.f; 
                bounds.position.x -= 10.f; bounds.size.x += 20.f;
                if (bounds.contains(mousePos)) {
                    float pct = (mousePos.x - bg.getPosition().x) / bg.getSize().x;
                    if (pct < 0.f) pct = 0.f;
                    if (pct > 1.f) pct = 1.f;
                    volume = (pct * pct) * 100.f;
                    refreshSettingsDisplay();
                }
            };

            if (audioSettings) {
                updateSlider(musicSliderBg, audioSettings->musicVolume);
                updateSlider(blackjackSfxSliderBg, audioSettings->blackjackSfxVolume);
                updateSlider(rouletteSfxSliderBg, audioSettings->rouletteSfxVolume);
                updateSlider(slotsSfxSliderBg, audioSettings->slotsSfxVolume);
            }
        }

        window.draw(overlay);
        window.draw(settingsPanel);
        window.draw(settingsTitleText);
        window.draw(musicSliderBg);
        window.draw(blackjackSfxSliderBg);
        window.draw(rouletteSfxSliderBg);
        window.draw(slotsSfxSliderBg);
        window.draw(musicSliderFill);
        window.draw(blackjackSfxSliderFill);
        window.draw(rouletteSfxSliderFill);
        window.draw(slotsSfxSliderFill);
        window.draw(musicLabelText);
        window.draw(blackjackSfxLabelText);
        window.draw(rouletteSfxLabelText);
        window.draw(slotsSfxLabelText);
        window.draw(settingsCloseButton);
        window.draw(settingsCloseText);
    }
    else if (showingBankrollInput)
    {
        window.draw(overlay);
        window.draw(popupPanel);
        window.draw(bankrollLabelText);
        window.draw(bankrollBox);
        window.draw(bankrollInputText);

        if (bankrollHintText.getString() != "")
        {
            window.draw(bankrollHintText);
        }

        if (errorText.getString() != "")
        {
            window.draw(errorText);
        }

        window.draw(confirmButton);
        window.draw(cancelButton);
        window.draw(confirmText);
        window.draw(cancelText);
    }
}