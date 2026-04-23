/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Header for the SlotsStats class tracking cumulative slots session statistics.
 */

#ifndef SLOTSSTATS_H
#define SLOTSSTATS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct SlotsRoundSummary
{
    double betAmount;
    double payoutAmount;
    double netChange;
    bool wasThreeInARow;
    bool wasJackpot;    // bar or seven triple
};

class SlotsStats
{
private:
    int totalRounds;
    int totalWins;
    int totalLosses;

    double totalAmountBet;
    double totalPayoutReceived;
    double biggestWin;
    double biggestLoss;

    int threeInARowHits;
    int jackpotHits;

    // (Terminal format helpers removed)

public:
    SlotsStats(double startingBankroll = 0.0);

    void recordRound(const SlotsRoundSummary& summary);

    // Getters
    int    getTotalRounds()        const;
    int    getTotalWins()          const;
    int    getTotalLosses()        const;
    double getTotalAmountBet()     const;
    double getTotalPayoutReceived() const;
    double getNetProfit()          const;
    double getBiggestWin()         const;
    double getBiggestLoss()        const;
    double getWinRate()            const;
    int    getThreeInARowHits()    const;
    int    getJackpotHits()        const;
};

#endif
