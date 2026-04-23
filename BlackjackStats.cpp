/*
    Name:       Prayush Panta
    UID:        PP1008
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include "BlackjackStats.h"
#include <algorithm>
#include <cmath>

using std::string;


//  Constructor

BlackjackStats::BlackjackStats(double startBankroll)
    : totalRounds(0),
      totalWins(0),
      totalLosses(0),
      totalPushes(0),
      totalBlackjacks(0),
      totalPlayerBusts(0),
      totalDealerBusts(0),
      totalDoubleDowns(0),
      totalDoubleDownWins(0),
      startingBankroll(startBankroll),
      currentBankroll(startBankroll),
      totalAmountBet(0.0),
      totalPayoutReceived(0.0),
      biggestWin(0.0),
      biggestLoss(0.0),
      peakBankroll(startBankroll),
      lowestBankroll(startBankroll),
      currentStreak(0),
      longestWinStreak(0),
      longestLossStreak(0)
{
}


//  recordRound — call after every game.getRoundSummary()

void BlackjackStats::recordRound(const BlackjackRoundSummary& summary)
{
    totalRounds++;

    //  Outcome counters 
    if (summary.playerWon)
    {
        totalWins++;
        currentStreak = (currentStreak > 0) ? currentStreak + 1 : 1;
        longestWinStreak = std::max(longestWinStreak, currentStreak);
    }
    else if (summary.dealerWon)
    {
        totalLosses++;
        currentStreak = (currentStreak < 0) ? currentStreak - 1 : -1;
        longestLossStreak = std::max(longestLossStreak, std::abs(currentStreak));
    }
    else if (summary.push)
    {
        totalPushes++;
        currentStreak = 0;
    }

    if (summary.wasNaturalBlackjack) totalBlackjacks++;
    if (summary.dealerBusted)        totalDealerBusts++;

    //  Player bust: derive from roundOutcome 
    //    BlackjackRoundSummary has no playerBusted field;
    //    PlayerBust outcome means the player busted.
    if (summary.roundOutcome == RoundOutcome::PlayerBust)
        totalPlayerBusts++;

    //  Double down: derive from hand-level data 
    //    BlackjackRoundSummary has no wasDoubleDown field;
    //    check each player hand's doubledDown flag instead.
    for (const SplitHandState& hand : summary.playerHands)
    {
        if (hand.doubledDown)
        {
            totalDoubleDowns++;
            if (hand.won) totalDoubleDownWins++;
        }
    }

    //  Financial tracking 
    //    Use initialBetAmount (not betAmount — that field doesn't exist).
    totalAmountBet      += summary.initialBetAmount;
    totalPayoutReceived += summary.payoutAmount;
    currentBankroll      = summary.endingBankroll;

    if (summary.netChange > 0.0)
        biggestWin  = std::max(biggestWin,  summary.netChange);
    else if (summary.netChange < 0.0)
        biggestLoss = std::max(biggestLoss, std::abs(summary.netChange));

    peakBankroll   = std::max(peakBankroll,   currentBankroll);
    lowestBankroll = std::min(lowestBankroll, currentBankroll);

    //  History (last 10 rounds) 
    RoundResult result;
    result.roundNumber   = summary.roundNumber;
    result.netChange     = summary.netChange;
    result.bankrollAfter = summary.endingBankroll;

    switch (summary.roundOutcome)
    {
        case RoundOutcome::PlayerBlackjack: result.outcome = "BLACKJACK";    break;
        case RoundOutcome::PlayerWin:       result.outcome = "WIN";          break;
        case RoundOutcome::DealerBust:      result.outcome = "WIN (D.Bust)"; break;
        case RoundOutcome::Push:            result.outcome = "PUSH";         break;
        case RoundOutcome::PlayerBust:      result.outcome = "LOSS (Bust)";  break;
        case RoundOutcome::DealerWin:       result.outcome = "LOSS";         break;
        case RoundOutcome::DealerBlackjack: result.outcome = "LOSS (D.BJ)";  break;
        default:                            result.outcome = "---";          break;
    }

    history.push_back(result);
    if (history.size() > 10)
        history.erase(history.begin());
}


// (Terminal display functions removed)


//  Getters

int    BlackjackStats::getTotalRounds()       const { return totalRounds; }
int    BlackjackStats::getTotalWins()         const { return totalWins; }
int    BlackjackStats::getTotalLosses()       const { return totalLosses; }
int    BlackjackStats::getTotalPushes()       const { return totalPushes; }
int    BlackjackStats::getTotalBlackjacks()   const { return totalBlackjacks; }
int    BlackjackStats::getTotalPlayerBusts()  const { return totalPlayerBusts; }
int    BlackjackStats::getTotalDealerBusts()  const { return totalDealerBusts; }
int    BlackjackStats::getTotalDoubleDowns()  const { return totalDoubleDowns; }
int    BlackjackStats::getLongestWinStreak()  const { return longestWinStreak; }
int    BlackjackStats::getLongestLossStreak() const { return longestLossStreak; }
int    BlackjackStats::getCurrentStreak()     const { return currentStreak; }

double BlackjackStats::getStartingBankroll()    const { return startingBankroll; }
double BlackjackStats::getCurrentBankroll()     const { return currentBankroll; }
double BlackjackStats::getNetProfit()           const { return currentBankroll - startingBankroll; }
double BlackjackStats::getTotalAmountBet()      const { return totalAmountBet; }
double BlackjackStats::getTotalPayoutReceived() const { return totalPayoutReceived; }
double BlackjackStats::getBiggestWin()          const { return biggestWin; }
double BlackjackStats::getBiggestLoss()         const { return biggestLoss; }
double BlackjackStats::getPeakBankroll()        const { return peakBankroll; }
double BlackjackStats::getLowestBankroll()      const { return lowestBankroll; }

double BlackjackStats::getWinRate() const
{
    int decided = totalWins + totalLosses;
    return decided > 0 ? (double)totalWins / decided : 0.0;
}

double BlackjackStats::getROI() const
{
    return totalAmountBet > 0
        ? (currentBankroll - startingBankroll) / totalAmountBet
        : 0.0;
}
