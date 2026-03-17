#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include <string>
#include <vector>
#include "Shoe.h"
#include "Hand.h"
#include "BlackjackTypes.h"

using std::string;
using std::vector;

class BlackjackGame
{
private:
    Shoe shoe;
    Hand playerHand;
    Hand dealerHand;

    double bankroll;
    double currentBet;
    double payoutAmount;
    double startingBankrollForRound;

    int roundNumber;
    int reshuffleCutoff;

    bool dealerHoleCardRevealed;
    bool lastHandBeforeShuffle;
    bool reshufflePending;
    bool reshuffledBeforeCurrentRound;
    bool playerDoubledDown;

    RoundState roundState;
    RoundOutcome roundOutcome;

    string roundResultText;
    vector<string> roundLog;
    vector<string> playerActionSequence;

    void addLogEntry(const string& entry);
    void dealInitialCards();
    void revealDealerHoleCard();
    void playDealerTurn();
    void resolveRound();
    string formatMoney(double amount) const;
    string outcomeToString() const;

public:
    BlackjackGame(double startingBankroll, int numberOfDecks = 6);

    bool startNewRound(double betAmount);

    bool canHit() const;
    bool canStand() const;
    bool canDoubleDown() const;

    void playerHit();
    void playerStand();
    void playerDoubleDown();

    double getBankroll() const;
    double getCurrentBet() const;
    double getPayoutAmount() const;

    int getRoundNumber() const;
    int getCardsRemaining() const;
    int getReshuffleCutoff() const;

    int getPlayerValue() const;
    int getDealerValue() const;

    Hand getPlayerHand() const;
    Hand getDealerHand() const;

    RoundState getRoundState() const;
    RoundOutcome getRoundOutcome() const;

    BlackjackRoundSummary getRoundSummary() const;

    string getRoundResultText() const;

    bool isRoundOver() const;
    bool isDealerHoleCardRevealed() const;
    bool isLastHandBeforeShuffle() const;
    bool isReshufflePending() const;
    bool wasShoeReshuffledBeforeCurrentRound() const;
    bool didPlayerDoubleDown() const;

    vector<string> getRoundLog() const;
    void clearRoundLog();
};

#endif