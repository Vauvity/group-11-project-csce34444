#include "BlackjackGame.h"
#include <sstream>
#include <iomanip>

using std::fixed;
using std::ostringstream;
using std::setprecision;

BlackjackGame::BlackjackGame(double startingBankroll, int numberOfDecks)
    : shoe(numberOfDecks),
      bankroll(startingBankroll),
      currentBet(0.0),
      payoutAmount(0.0),
      startingBankrollForRound(0.0),
      roundNumber(0),
      reshuffleCutoff(52),
      dealerHoleCardRevealed(false),
      lastHandBeforeShuffle(false),
      reshufflePending(false),
      reshuffledBeforeCurrentRound(false),
      playerDoubledDown(false),
      roundState(RoundState::WaitingForBet),
      roundOutcome(RoundOutcome::None),
      roundResultText("")
{
}

bool BlackjackGame::startNewRound(double betAmount)
{
    if (roundState != RoundState::WaitingForBet && roundState != RoundState::RoundOver)
    {
        return false;
    }

    if (betAmount <= 0.0 || betAmount > bankroll)
    {
        return false;
    }

    reshuffledBeforeCurrentRound = false;

    if (reshufflePending)
    {
        shoe.reset();
        reshufflePending = false;
        reshuffledBeforeCurrentRound = true;
    }

    playerHand.clear();
    dealerHand.clear();
    roundLog.clear();

    playerActionSequence.clear();
    startingBankrollForRound = bankroll;

    currentBet = betAmount;
    payoutAmount = 0.0;
    playerDoubledDown = false;
    dealerHoleCardRevealed = false;
    roundOutcome = RoundOutcome::None;
    roundResultText = "";

    roundNumber++;

    lastHandBeforeShuffle = shoe.getCardsRemaining() <= reshuffleCutoff;

    bankroll -= currentBet;
    roundState = RoundState::PlayerTurn;

    addLogEntry("========================================");
    addLogEntry("Round " + std::to_string(roundNumber) + " started.");
    if (reshuffledBeforeCurrentRound)
    {
        addLogEntry("Shoe reshuffled before this round.");
    }

    addLogEntry("Starting bankroll before bet: " + formatMoney(bankroll + currentBet));
    addLogEntry("Bet placed: " + formatMoney(currentBet));
    addLogEntry("Bankroll after bet deduction: " + formatMoney(bankroll));

    if (lastHandBeforeShuffle)
    {
        addLogEntry("Last hand before shuffle.");
    }

    dealInitialCards();

    if (playerHand.isBlackjack() || dealerHand.isBlackjack())
    {
        revealDealerHoleCard();
        resolveRound();
    }

    return true;
}

void BlackjackGame::addLogEntry(const string& entry)
{
    roundLog.push_back(entry);
}

void BlackjackGame::dealInitialCards()
{
    Card playerCard1 = shoe.dealCard();
    playerHand.addCard(playerCard1);
    addLogEntry("Player dealt: " + playerCard1.toString());

    Card dealerCard1 = shoe.dealCard();
    dealerHand.addCard(dealerCard1);
    addLogEntry("Dealer dealt: " + dealerCard1.toString() + " (up card)");

    Card playerCard2 = shoe.dealCard();
    playerHand.addCard(playerCard2);
    addLogEntry("Player dealt: " + playerCard2.toString());

    Card dealerCard2 = shoe.dealCard();
    dealerHand.addCard(dealerCard2);
    addLogEntry("Dealer dealt: " + dealerCard2.toString() + " (hole card)");

    addLogEntry("Player starting hand: " + playerHand.toString() +
                " | value = " + std::to_string(playerHand.getValue()));
    addLogEntry("Dealer showing: " + dealerCard1.toString());
}

void BlackjackGame::revealDealerHoleCard()
{
    if (!dealerHoleCardRevealed)
    {
        dealerHoleCardRevealed = true;
        addLogEntry("Dealer hole card revealed. Dealer hand: " + dealerHand.toString() +
                    " | value = " + std::to_string(dealerHand.getValue()));
    }
}

bool BlackjackGame::canHit() const
{
    return roundState == RoundState::PlayerTurn && !playerHand.isBust();
}

bool BlackjackGame::canStand() const
{
    return roundState == RoundState::PlayerTurn;
}

bool BlackjackGame::canDoubleDown() const
{
    return roundState == RoundState::PlayerTurn &&
           playerHand.getCards().size() == 2 &&
           bankroll >= currentBet;
}

void BlackjackGame::playerHit()
{
    if (!canHit())
    {
        return;
    }

    Card newCard = shoe.dealCard();
    playerHand.addCard(newCard);

    addLogEntry("Player action: Hit");
    playerActionSequence.push_back("Hit");
    addLogEntry("Player draws: " + newCard.toString());
    addLogEntry("Player hand: " + playerHand.toString() +
                " | value = " + std::to_string(playerHand.getValue()));

    if (playerHand.isBust())
    {
        addLogEntry("Player busts.");
        revealDealerHoleCard();
        resolveRound();
    }
}

void BlackjackGame::playerStand()
{
    if (!canStand())
    {
        return;
    }

    addLogEntry("Player action: Stand");
    playerActionSequence.push_back("Stand");
    roundState = RoundState::DealerTurn;

    playDealerTurn();
    resolveRound();
}

void BlackjackGame::playerDoubleDown()
{
    if (!canDoubleDown())
    {
        return;
    }

    addLogEntry("Player action: Double Down");
    playerActionSequence.push_back("DoubleDown");

    bankroll -= currentBet;
    currentBet *= 2.0;
    playerDoubledDown = true;

    addLogEntry("Bet doubled to: " + formatMoney(currentBet));
    addLogEntry("Bankroll after double down deduction: " + formatMoney(bankroll));

    Card newCard = shoe.dealCard();
    playerHand.addCard(newCard);

    addLogEntry("Player draws: " + newCard.toString());
    addLogEntry("Player hand: " + playerHand.toString() +
                " | value = " + std::to_string(playerHand.getValue()));

    if (playerHand.isBust())
    {
        addLogEntry("Player busts after double down.");
        revealDealerHoleCard();
        resolveRound();
        return;
    }

    addLogEntry("Double down completes player turn.");
    roundState = RoundState::DealerTurn;

    playDealerTurn();
    resolveRound();
}

void BlackjackGame::playDealerTurn()
{
    revealDealerHoleCard();

    while (dealerHand.getValue() < 17)
    {
        Card newCard = shoe.dealCard();
        dealerHand.addCard(newCard);

        addLogEntry("Dealer draws: " + newCard.toString());
        addLogEntry("Dealer hand: " + dealerHand.toString() +
                    " | value = " + std::to_string(dealerHand.getValue()));
    }

    int dealerValue = dealerHand.getValue();

    if (dealerHand.isBust())
    {
        addLogEntry("Dealer busts with value = " + std::to_string(dealerValue));
    }
    else
    {
        addLogEntry("Dealer stands with value = " + std::to_string(dealerValue));
    }
}

void BlackjackGame::resolveRound()
{
    int playerValue = playerHand.getValue();
    int dealerValue = dealerHand.getValue();

    payoutAmount = 0.0;

    if (playerHand.isBlackjack() && dealerHand.isBlackjack())
    {
        roundOutcome = RoundOutcome::Push;
        payoutAmount = currentBet;
        bankroll += payoutAmount;
        roundResultText = "Push. Both player and dealer have blackjack.";
    }
    else if (playerHand.isBlackjack())
    {
        roundOutcome = RoundOutcome::PlayerBlackjack;
        payoutAmount = currentBet * 2.5;
        bankroll += payoutAmount;
        roundResultText = "Player wins with natural blackjack.";
    }
    else if (dealerHand.isBlackjack())
    {
        roundOutcome = RoundOutcome::DealerBlackjack;
        payoutAmount = 0.0;
        roundResultText = "Dealer wins with natural blackjack.";
    }
    else if (playerHand.isBust())
    {
        roundOutcome = RoundOutcome::PlayerBust;
        payoutAmount = 0.0;
        roundResultText = "Player busts. Dealer wins.";
    }
    else if (dealerHand.isBust())
    {
        roundOutcome = RoundOutcome::DealerBust;
        payoutAmount = currentBet * 2.0;
        bankroll += payoutAmount;
        roundResultText = "Dealer busts. Player wins.";
    }
    else if (playerValue > dealerValue)
    {
        roundOutcome = RoundOutcome::PlayerWin;
        payoutAmount = currentBet * 2.0;
        bankroll += payoutAmount;
        roundResultText = "Player wins.";
    }
    else if (dealerValue > playerValue)
    {
        roundOutcome = RoundOutcome::DealerWin;
        payoutAmount = 0.0;
        roundResultText = "Dealer wins.";
    }
    else
    {
        roundOutcome = RoundOutcome::Push;
        payoutAmount = currentBet;
        bankroll += payoutAmount;
        roundResultText = "Push.";
    }

    addLogEntry("Final player hand: " + playerHand.toString() +
                " | value = " + std::to_string(playerValue));
    addLogEntry("Final dealer hand: " + dealerHand.toString() +
                " | value = " + std::to_string(dealerValue));
    addLogEntry("Round outcome: " + outcomeToString());
    addLogEntry("Payout returned to bankroll: " + formatMoney(payoutAmount));
    addLogEntry("Ending bankroll: " + formatMoney(bankroll));

    if (lastHandBeforeShuffle)
    {
        reshufflePending = true;
        addLogEntry("Shoe will be reshuffled before the next round.");
    }

    roundState = RoundState::RoundOver;
}

string BlackjackGame::formatMoney(double amount) const
{
    ostringstream out;
    out << "$" << fixed << setprecision(2) << amount;
    return out.str();
}

string BlackjackGame::outcomeToString() const
{
    switch (roundOutcome)
    {
        case RoundOutcome::PlayerWin:
            return "Player Win";
        case RoundOutcome::DealerWin:
            return "Dealer Win";
        case RoundOutcome::Push:
            return "Push";
        case RoundOutcome::PlayerBlackjack:
            return "Player Blackjack";
        case RoundOutcome::PlayerBust:
            return "Player Bust";
        case RoundOutcome::DealerBust:
            return "Dealer Bust";
        case RoundOutcome::DealerBlackjack:
            return "Dealer Blackjack";
        case RoundOutcome::None:
        default:
            return "None";
    }
}

double BlackjackGame::getBankroll() const
{
    return bankroll;
}

double BlackjackGame::getCurrentBet() const
{
    return currentBet;
}

double BlackjackGame::getPayoutAmount() const
{
    return payoutAmount;
}

int BlackjackGame::getRoundNumber() const
{
    return roundNumber;
}

int BlackjackGame::getCardsRemaining() const
{
    return shoe.getCardsRemaining();
}

int BlackjackGame::getReshuffleCutoff() const
{
    return reshuffleCutoff;
}

int BlackjackGame::getPlayerValue() const
{
    return playerHand.getValue();
}

int BlackjackGame::getDealerValue() const
{
    return dealerHand.getValue();
}

Hand BlackjackGame::getPlayerHand() const
{
    return playerHand;
}

Hand BlackjackGame::getDealerHand() const
{
    return dealerHand;
}

RoundState BlackjackGame::getRoundState() const
{
    return roundState;
}

RoundOutcome BlackjackGame::getRoundOutcome() const
{
    return roundOutcome;
}

string BlackjackGame::getRoundResultText() const
{
    return roundResultText;
}

BlackjackRoundSummary BlackjackGame::getRoundSummary() const
{
    BlackjackRoundSummary summary;

    summary.roundNumber = roundNumber;

    summary.startingBankroll = startingBankrollForRound;
    summary.betAmount = currentBet;
    summary.bankrollAfterBetDeduction = startingBankrollForRound - currentBet;
    summary.payoutAmount = payoutAmount;
    summary.endingBankroll = bankroll;
    summary.netChange = bankroll - startingBankrollForRound;

    summary.roundOutcome = roundOutcome;

    summary.playerFinalValue = playerHand.getValue();
    summary.dealerFinalValue = dealerHand.getValue();

    summary.playerWon =
        (roundOutcome == RoundOutcome::PlayerWin ||
         roundOutcome == RoundOutcome::PlayerBlackjack ||
         roundOutcome == RoundOutcome::DealerBust);

    summary.dealerWon =
        (roundOutcome == RoundOutcome::DealerWin ||
         roundOutcome == RoundOutcome::DealerBlackjack ||
         roundOutcome == RoundOutcome::PlayerBust);

    summary.push = (roundOutcome == RoundOutcome::Push);

    summary.wasNaturalBlackjack =
        (roundOutcome == RoundOutcome::PlayerBlackjack);

    summary.playerBusted =
        (roundOutcome == RoundOutcome::PlayerBust);

    summary.dealerBusted =
        (roundOutcome == RoundOutcome::DealerBust);

    summary.wasDoubleDown = playerDoubledDown;

    summary.playerCards.clear();
    for (const Card& card : playerHand.getCards())
    {
        summary.playerCards.push_back(card.toString());
    }

    summary.dealerCards.clear();
    for (const Card& card : dealerHand.getCards())
    {
        summary.dealerCards.push_back(card.toString());
    }

    summary.playerActionSequence = playerActionSequence;

    summary.lastHandBeforeShuffle = lastHandBeforeShuffle;
    summary.reshuffledBeforeRound = reshuffledBeforeCurrentRound;
    summary.cardsRemainingAfterRound = shoe.getCardsRemaining();

    return summary;
}

bool BlackjackGame::isRoundOver() const
{
    return roundState == RoundState::RoundOver;
}

bool BlackjackGame::isDealerHoleCardRevealed() const
{
    return dealerHoleCardRevealed;
}

bool BlackjackGame::isLastHandBeforeShuffle() const
{
    return lastHandBeforeShuffle;
}

bool BlackjackGame::isReshufflePending() const
{
    return reshufflePending;
}

bool BlackjackGame::wasShoeReshuffledBeforeCurrentRound() const
{
    return reshuffledBeforeCurrentRound;
}

bool BlackjackGame::didPlayerDoubleDown() const
{
    return playerDoubledDown;
}

vector<string> BlackjackGame::getRoundLog() const
{
    return roundLog;
}

void BlackjackGame::clearRoundLog()
{
    roundLog.clear();
}