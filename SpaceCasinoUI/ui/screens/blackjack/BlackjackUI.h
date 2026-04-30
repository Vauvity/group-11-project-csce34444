#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "../../../core/blackjack/BlackjackGame.h"
#include "../../../core/blackjack/Card.h"
#include "../../../core/session/SessionStats.h"

class BlackjackUI
{
public:
    explicit BlackjackUI(sf::Font& sharedFont);

    void setStartingBankroll(double bankroll);
    double getCurrentBankroll() const;

    void handleScreenClick(sf::Vector2f mousePos, bool& backToMenu);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();
    void draw(sf::RenderWindow& window);
    void setSessionStats(SessionStats* stats);

private:
    BlackjackGame game;
    sf::Font& font;

    sf::Text titleText;
    sf::Text bankrollText;
    sf::Text betText;

    sf::RectangleShape betBg;
    sf::Text dealerText;
    sf::Text playerText;
    sf::Text messageText;
    sf::Text statsText;

    sf::RectangleShape hitButton;
    sf::RectangleShape standButton;
    sf::RectangleShape doubleButton;
    sf::RectangleShape splitButton;
    sf::RectangleShape newRoundButton;
    sf::RectangleShape backButton;

    sf::Text hitText;
    sf::Text standText;
    sf::Text doubleText;
    sf::Text splitText;
    sf::Text newRoundText;
    sf::Text backText;
    sf::Text hintText;

    sf::RectangleShape hintButton;

    std::string currentHint;

    float currentBet;
    std::string betInput;
    bool enteringBet;

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
    bool roundStarted;
    SessionStats* sessionStats;
    int lastRecordedRoundNumber;

    void setupButtons();
    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);

    std::string getDealerDisplay() const;
    std::string getPlayerDisplay() const;
    std::string getStatusMessage() const;
    std::string shortenResultText(const std::string& fullText) const;
    void commitBetInput();

    std::map<std::string, sf::Texture> cardTextures;
    sf::Texture cardBackTexture;

    void loadCardTextures();
    std::string rankToString(Rank r) const;
    std::string suitToString(Suit s) const;

    std::string getPostRoundStats() const;

    void updateText();
    void handleGameClick(sf::Vector2f mousePos);
    void recordRoundIfNeeded();
};