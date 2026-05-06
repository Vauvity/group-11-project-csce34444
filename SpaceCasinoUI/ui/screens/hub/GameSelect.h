#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../../../core/audio/AudioSettings.h"

class GameSelect
{
public:
    explicit GameSelect(sf::Font& sharedFont);

    void handleMouseClick(sf::Vector2f mousePos, bool& openBlackjack, bool& openRoulette, bool& openSlots, bool& openStats, bool& backToMain);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();

    void setBankroll(double bankroll);
    double getBankroll() const;

    void setAudioSettings(AudioSettings* settings);

    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;

    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text messageText;
    sf::Text bankrollText;

    sf::RectangleShape blackjackButton;
    sf::RectangleShape rouletteButton;
    sf::RectangleShape slotsButton;
    sf::RectangleShape statsButton;
    sf::RectangleShape backButton;
    sf::RectangleShape settingsButton;

    sf::Text blackjackText;
    sf::Text rouletteText;
    sf::Text slotsText;
    sf::Text statsText;
    sf::Text backText;
    sf::Text settingsText;

    sf::RectangleShape blackjackInfoBtn;
    sf::RectangleShape rouletteInfoBtn;
    sf::RectangleShape slotsInfoBtn;
    
    sf::Text blackjackInfoText;
    sf::Text rouletteInfoText;
    sf::Text slotsInfoText;

    sf::RectangleShape overlay;
    sf::RectangleShape popupPanel;
    sf::RectangleShape addMoneyBox;
    sf::RectangleShape addConfirmButton;
    sf::RectangleShape addCancelButton;

    sf::Text addMoneyLabelText;
    sf::Text addMoneyInputText;
    sf::Text addHintText;
    sf::Text addErrorText;
    sf::Text addConfirmText;
    sf::Text addCancelText;

    bool showingGameOverPopup;
    sf::RectangleShape gameOverPanel;
    sf::Text gameOverTitle;
    sf::Text gameOverMessage;
    sf::RectangleShape gameOverButton;
    sf::Text gameOverButtonText;

    bool showingInfoPopup;
    sf::RectangleShape infoPanel;
    sf::Text infoTitleText;
    sf::Text infoBodyText;
    sf::RectangleShape infoCloseButton;
    sf::Text infoCloseText;

    bool showingSettingsPopup;
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

    double currentBankroll;
    std::string addMoneyInput;
    bool showingAddMoneyPopup;

    AudioSettings* audioSettings;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void refreshBankrollDisplay();
    void refreshAddMoneyDisplay();
    void refreshSettingsDisplay();
    bool hasValidAddAmount() const;
};