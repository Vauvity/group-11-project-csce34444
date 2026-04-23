/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Header for the RouletteStats class tracking cumulative roulette session statistics.
 */

#ifndef ROULETTESTATS_H
#define ROULETTESTATS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct RouletteRoundSummary
{
    double betAmount;
    double payoutAmount;
    double netChange;
    bool wasStraightUp;
    bool straightUpWon;
};

class RouletteStats
{
private:
    int totalRounds;
    int totalWins;
    int totalLosses;

    double totalAmountBet;
    double totalPayoutReceived;
    double biggestWin;
    double biggestLoss;

    int straightUpHits;

    // (Terminal format helpers removed)

public:
    RouletteStats(double startingBankroll = 0.0);

    void recordRound(const RouletteRoundSummary& summary);

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
    int    getStraightUpHits()     const;
};

#endif
