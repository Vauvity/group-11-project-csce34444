/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Implementation of the SlotsStats class tracking cumulative slots session statistics.
 */

#include "SlotsStats.h"
#include <cmath>

using std::string;

// Constructor

SlotsStats::SlotsStats(double startBankroll)
    : totalRounds(0),
      totalWins(0),
      totalLosses(0),
      totalAmountBet(0.0),
      totalPayoutReceived(0.0),
      biggestWin(0.0),
      biggestLoss(0.0),
      threeInARowHits(0),
      jackpotHits(0)
{
}

// recordRound

void SlotsStats::recordRound(const SlotsRoundSummary& summary)
{
    totalRounds++;

    totalAmountBet      += summary.betAmount;
    totalPayoutReceived += summary.payoutAmount;

    if (summary.netChange > 0.0)
    {
        totalWins++;
        if (summary.netChange > biggestWin)
            biggestWin = summary.netChange;
    }
    else
    {
        totalLosses++;
        double loss = std::abs(summary.netChange);
        if (loss > biggestLoss)
            biggestLoss = loss;
    }

    if (summary.wasThreeInARow) threeInARowHits++;
    if (summary.wasJackpot)     jackpotHits++;
}

// (Terminal display functions removed)

// Getters

int    SlotsStats::getTotalRounds()        const { return totalRounds; }
int    SlotsStats::getTotalWins()          const { return totalWins; }
int    SlotsStats::getTotalLosses()        const { return totalLosses; }
double SlotsStats::getTotalAmountBet()     const { return totalAmountBet; }
double SlotsStats::getTotalPayoutReceived() const { return totalPayoutReceived; }
double SlotsStats::getNetProfit()          const { return totalPayoutReceived - totalAmountBet; }
double SlotsStats::getBiggestWin()         const { return biggestWin; }
double SlotsStats::getBiggestLoss()        const { return biggestLoss; }
int    SlotsStats::getThreeInARowHits()    const { return threeInARowHits; }
int    SlotsStats::getJackpotHits()        const { return jackpotHits; }

double SlotsStats::getWinRate() const
{
    return totalRounds > 0 ? (double)totalWins / totalRounds : 0.0;
}
