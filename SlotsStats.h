/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri
    SlotsStats.h
    Tracks cumulative Slots session statistics.
    recordRound() is called by SessionStats after every spin.
    displayStats() is triggered by the UI stats button via SessionStats.
*/


#ifndef SLOTSSTATS_H
#define SLOTSSTATS_H

#include <string>
#include <vector>
#include "SlotTypes.h"

using std::string;
using std::vector;

class SlotsStats
{
private:
    int totalSpins;
    int totalWins;
    int totalLosses;

    double startingBankroll;
    double currentBankroll;
    double totalAmountBet;
    double totalPayoutReceived;
    double biggestWin;
    double biggestLoss;
    double peakBankroll;
    double lowestBankroll;

    int currentStreak;
    int longestWinStreak;
    int longestLossStreak;

    struct SpinResult
    {
        int    spinNumber;
        string outcome;
        double netChange;
        double bankrollAfter;
    };
    vector<SpinResult> history;

    string formatMoney(double amount)               const;
    string formatPercent(double num, double den)    const;
    string buildBar(double ratio, int width)        const;
    void   printDivider(char c = '-', int w = 50)  const;
    void   printRow(const string& label, const string& value, int w = 50) const;

public:
    explicit SlotsStats(double startingBankroll);

    void recordRound(const SlotsSummary& summary);
    void displayStats() const;

    int    getTotalSpins()         const;
    int    getTotalWins()          const;
    int    getTotalLosses()        const;
    int    getLongestWinStreak()   const;
    int    getLongestLossStreak()  const;
    int    getCurrentStreak()      const;
    double getStartingBankroll()   const;
    double getCurrentBankroll()    const;
    double getNetProfit()          const;
    double getTotalAmountBet()     const;
    double getTotalPayoutReceived()const;
    double getBiggestWin()         const;
    double getBiggestLoss()        const;
    double getPeakBankroll()       const;
    double getLowestBankroll()     const;
    double getWinRate()            const;
    double getROI()                const;
};

#endif
