#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../../../core/roulette/RouletteGame.h"
#include "../../../core/roulette/RouletteBet.h"
#include "../../../core/roulette/RouletteTypes.h"
#include "../../../core/session/SessionStats.h"

class RouletteUI
{
public:
    explicit RouletteUI(sf::Font& sharedFont);

    void setStartingBankroll(double bankroll);
    double getCurrentBankroll() const;

    void handleScreenClick(sf::Vector2f mousePos, bool& backToMenu);
    void handleTextEntered(unsigned int unicode);
    void handleBackspace();

    void draw(sf::RenderWindow& window);
    void setSessionStats(SessionStats* stats);

private:
    RouletteGame game;
    sf::Font& font;

    sf::Text titleText;
    sf::Text bankrollText;
    sf::Text betText;

    sf::RectangleShape betBg;
    sf::Text selectedBetText;
    sf::Text numberInputLabelText;
    sf::Text numberInputText;
    sf::Text resultText;
    sf::Text payoutText;
    sf::Text spinText;
    sf::Text backText;
    sf::Text clearBetsText;
    sf::Text placeStraightText;

    sf::RectangleShape redButton;
    sf::RectangleShape blackButton;
    sf::RectangleShape evenButton;
    sf::RectangleShape oddButton;
    sf::RectangleShape lowButton;
    sf::RectangleShape highButton;
    sf::RectangleShape straightButton;
    sf::RectangleShape spinButton;
    sf::RectangleShape backButton;
    sf::RectangleShape clearBetsButton;
    sf::RectangleShape placeStraightButton;
    sf::RectangleShape numberBox;

    sf::Text redText;
    sf::Text blackText;
    sf::Text evenText;
    sf::Text oddText;
    sf::Text lowText;
    sf::Text highText;
    sf::Text straightText;

    struct UIChip {
        sf::Vector2f position;
        int amount;
    };
    std::vector<UIChip> placedChips;

    double currentBet;
    std::string chipInput;
    bool enteringChip;

    sf::Texture wheelTexture;
    sf::Sprite wheelSprite;

    sf::RectangleShape overlay;
    sf::RectangleShape popupPanel;
    sf::Text chipInputLabelText;
    sf::RectangleShape chipBox;
    sf::Text chipInputText;
    sf::Text chipHintText;
    sf::Text chipErrorText;
    sf::RectangleShape chipConfirmButton;
    sf::RectangleShape chipCancelButton;
    sf::Text chipConfirmText;
    sf::Text chipCancelText;

    void refreshChipInputDisplay();
    std::string numberInput;
    bool enteringNumber;

    enum class SelectedBet
    {
        Red,
        Black,
        Even,
        Odd,
        Low,
        High,
        Straight
    };
    bool hasSpun;
    SessionStats* sessionStats;

    sf::Clock ballAnimationClock;
    bool isBallSpinning;
    float ballAngle;

    void centerTextInButton(sf::Text& text, const sf::RectangleShape& button);
    void updateText();
    void spinRound();
    void commitChipInput();
    std::string getSelectedBetLabel() const;

    int getClickedTableNumber(sf::Vector2f mousePos) const;
    sf::FloatRect getTableCellBounds(int number) const;
    sf::FloatRect getZeroCellBounds() const;
    bool isRedNumber(int number) const;
};
