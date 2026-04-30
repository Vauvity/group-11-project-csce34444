#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../../../core/slots/SlotsGame.h"
#include "../../../core/slots/SlotWindow.h"
#include "../../../core/session/SessionStats.h"

class SlotsUI
{
public:
    explicit SlotsUI(sf::Font& sharedFont);

    void setStartingBankroll(double bankroll);
    double getCurrentBankroll() const;

    void handleScreenClick(sf::Vector2f mousePos, bool& backToMenu);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();
    void draw(sf::RenderWindow& window);
    void setSessionStats(SessionStats* stats);

private:
    Slots game;
    sf::Font& font;

    sf::Text titleText;
    sf::Text bankrollText;
    sf::Text betText;
    sf::Text jackpotText;
    sf::Text resultText;
    sf::Text payoutText;
    sf::Text backText;
    sf::Text spinText;

    sf::RectangleShape betBg;

    sf::RectangleShape spinButton;
    sf::RectangleShape backButton;

    SlotWindow currentWindow;
    bool hasSpun;
    double currentBet;
    std::string betInput;
    bool enteringBet;
    double lastPayout;
    
    sf::RectangleShape overlay;
    sf::RectangleShape popupPanel;
    sf::Text betInputLabelText;
    sf::RectangleShape betBox;
    sf::Text betInputText;
    sf::Text betHintText;
    sf::Text betErrorText;
    sf::RectangleShape betConfirmButton;
    sf::RectangleShape betCancelButton;
    sf::Text betConfirmText;
    sf::Text betCancelText;

    void refreshBetInputDisplay();
    SessionStats* sessionStats;
    int lastRecordedSpinNumber;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    std::string symbolToString(char c) const;

    std::map<char, sf::Texture> symbolTextures;
    void loadTextures();
    void updateText();
    void commitBetInput();
};
