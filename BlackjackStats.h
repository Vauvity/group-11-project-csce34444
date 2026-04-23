/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Header for the BlackjackStats class tracking cumulative blackjack session statistics.
 */

#ifndef BLACKJACKSTATS_H
#define BLACKJACKSTATS_H

#include <string>
#include <vector>
#include "../games/blackjack/BlackjackTypes.h"

using std::string;
using std::vector;

// Tracks and displays cumulative blackjack session statistics.
// Usage: after every round ends, call recordRound(game.getRoundSummary()).

class BlackjackStats
{
private:
    //  Round / hands count
    int totalRounds;
    int totalWins;
    int totalLosses;
    int totalPushes;
    int totalBlackjacks;
    int totalPlayerBusts;
    int totalDealerBusts;
    int totalDoubleDowns;
    int totalDoubleDownWins;

    //  Bankroll tracker
    double startingBankroll;
    double currentBankroll;
    double totalAmountBet;
    double totalPayoutReceived;
    double biggestWin;
    double biggestLoss;
    double peakBankroll;
    double lowestBankroll;

    //  WIN/Loss Streak tracking 
    int currentStreak;         // positive = win streak, negative = loss streak
    int longestWinStreak;
    int longestLossStreak;

    //  Round history
    struct RoundResult
    {
        int roundNumber;
        string outcome;
        double netChange;
        double bankrollAfter;
    };
    vector<RoundResult> history;

    // (Terminal format helpers removed)

public:
    // Pass in the starting bankroll once when the session begins
    BlackjackStats(double startingBankroll);

    // Call this after every round using game.getRoundSummary()
    void recordRound(const BlackjackRoundSummary& summary);

    //  Individual getters (for future app integration) 
    int   getTotalRounds()       const;
    int   getTotalWins()         const;
    int   getTotalLosses()       const;
    int   getTotalPushes()       const;
    int   getTotalBlackjacks()   const;
    int   getTotalPlayerBusts()  const;
    int   getTotalDealerBusts()  const;
    int   getTotalDoubleDowns()  const;
    int   getLongestWinStreak()  const;
    int   getLongestLossStreak() const;
    int   getCurrentStreak()     const;

    double getStartingBankroll()    const;
    double getCurrentBankroll()     const;
    double getNetProfit()           const;
    double getTotalAmountBet()      const;
    double getTotalPayoutReceived() const;
    double getBiggestWin()          const;
    double getBiggestLoss()         const;
    double getPeakBankroll()        const;
    double getLowestBankroll()      const;
    double getWinRate()             const;  // wins / (wins + losses)
    double getROI()                 const;  // net profit / total amount bet
};

#endif
