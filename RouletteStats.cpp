/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Implementation of the RouletteStats class tracking cumulative roulette session statistics.
 */

#include "RouletteStats.h"
#include <cmath>

using std::string;

// Constructor

RouletteStats::RouletteStats(double startBankroll)
    : totalRounds(0),
      totalWins(0),
      totalLosses(0),
      totalAmountBet(0.0),
      totalPayoutReceived(0.0),
      biggestWin(0.0),
      biggestLoss(0.0),
      straightUpHits(0)
{
}

// recordRound

void RouletteStats::recordRound(const RouletteRoundSummary& summary)
{
    totalRounds++;

    totalAmountBet      += summary.betAmount;
    totalPayoutReceived += summary.payoutAmount;

    if (summary.netChange > 0.0)
    {
        totalWins++;
        if (summary.netChange > biggestWin)
            biggestWin = summary.netChange;
        if (summary.wasStraightUp && summary.straightUpWon)
            straightUpHits++;
    }
    else
    {
        totalLosses++;
        double loss = std::abs(summary.netChange);
        if (loss > biggestLoss)
            biggestLoss = loss;
    }
}

// (Terminal display functions removed)

// Getters

int    RouletteStats::getTotalRounds()        const { return totalRounds; }
int    RouletteStats::getTotalWins()          const { return totalWins; }
int    RouletteStats::getTotalLosses()        const { return totalLosses; }
double RouletteStats::getTotalAmountBet()     const { return totalAmountBet; }
double RouletteStats::getTotalPayoutReceived() const { return totalPayoutReceived; }
double RouletteStats::getNetProfit()          const { return totalPayoutReceived - totalAmountBet; }
double RouletteStats::getBiggestWin()         const { return biggestWin; }
double RouletteStats::getBiggestLoss()        const { return biggestLoss; }
int    RouletteStats::getStraightUpHits()     const { return straightUpHits; }

double RouletteStats::getWinRate() const
{
    return totalRounds > 0 ? (double)totalWins / totalRounds : 0.0;
}
