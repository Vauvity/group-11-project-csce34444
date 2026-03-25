#ifndef BLACKJACKTYPES_H
#define BLACKJACKTYPES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

enum class PlayerAction
{
    Hit,
    Stand,
    DoubleDown
};

enum class RoundState
{
    WaitingForBet,
    PlayerTurn,
    DealerTurn,
    RoundOver
};

enum class RoundOutcome
{
    None,
    PlayerWin,
    DealerWin,
    Push,
    PlayerBlackjack,
    PlayerBust,
    DealerBust,
    DealerBlackjack
};

struct BlackjackRoundSummary
{
    int roundNumber;

    double startingBankroll;
    double betAmount;
    double bankrollAfterBetDeduction;
    double payoutAmount;
    double endingBankroll;
    double netChange;

    RoundOutcome roundOutcome;

    int playerFinalValue;
    int dealerFinalValue;

    bool playerWon;
    bool dealerWon;
    bool push;
    bool wasNaturalBlackjack;
    bool playerBusted;
    bool dealerBusted;
    bool wasDoubleDown;

    vector<string> playerCards;
    vector<string> dealerCards;
    vector<string> playerActionSequence;

    bool lastHandBeforeShuffle;
    bool reshuffledBeforeRound;
    int cardsRemainingAfterRound;
};

#endif