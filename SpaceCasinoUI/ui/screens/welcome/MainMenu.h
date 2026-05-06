#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../../../core/audio/AudioSettings.h"

class MainMenu
{
public:
    explicit MainMenu(sf::Font& sharedFont);

    void handleMouseClick(sf::Vector2f mousePos, bool& startGame, bool& exitGame);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();

    bool hasValidBankroll() const;
    double getEnteredBankroll() const;
    void resetSession();

    void setAudioSettings(AudioSettings* settings);

    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Text titleText;
    sf::Text bankrollLabelText;
    sf::Text bankrollInputText;
    sf::Text bankrollHintText;
    sf::Text errorText;

    sf::Text startText;
    sf::Text exitText;
    sf::Text confirmText;
    sf::Text cancelText;

    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape settingsButton;
    sf::Text settingsText;

    sf::RectangleShape overlay;
    sf::RectangleShape popupPanel;
    sf::RectangleShape bankrollBox;
    sf::RectangleShape confirmButton;
    sf::RectangleShape cancelButton;

    std::string bankrollInput;
    bool showingBankrollInput = false;
    bool bankrollSetForSession = false;
    
    bool showingSettingsPopup = false;
    sf::RectangleShape settingsPanel;
    sf::Text settingsTitleText;
    sf::RectangleShape musicSliderBg;
    sf::RectangleShape blackjackSfxSliderBg;
    sf::RectangleShape rouletteSfxSliderBg;
    sf::RectangleShape slotsSfxSliderBg;
    sf::RectangleShape musicSliderFill;
    sf::RectangleShape blackjackSfxSliderFill;
    sf::RectangleShape rouletteSfxSliderFill;
    sf::RectangleShape slotsSfxSliderFill;
    sf::Text musicLabelText;
    sf::Text blackjackSfxLabelText;
    sf::Text rouletteSfxLabelText;
    sf::Text slotsSfxLabelText;
    sf::RectangleShape settingsCloseButton;
    sf::Text settingsCloseText;

    AudioSettings* audioSettings = nullptr;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void refreshBankrollText();
    void refreshSettingsDisplay();
};