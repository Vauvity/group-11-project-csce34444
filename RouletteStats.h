/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri

    RouletteStats.h
    Tracks cumulative Roulette session statistics including bet type breakdown.
    recordRound() is called by SessionStats after every spin.
    displayStats() is triggered by the UI stats button via SessionStats.
*/

#ifndef ROULETTESTATS_H
#define ROULETTESTATS_H

#include <string>
#include <vector>
#include "RouletteTypes.h"

using std::string;
using std::vector;

class RouletteStats
{
private:
    int totalRounds;
    int totalWins;
    int totalLosses;

    // Bet type breakdown
    int colorBets;   int colorWins;
    int numberBets;  int numberWins;
    int bothBets;    int bothWins;

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

    struct RoundResult
    {
        int    roundNumber;
        string betType;
        string outcome;
        double netChange;
        double bankrollAfter;
    };
    vector<RoundResult> history;

    string formatMoney(double amount)               const;
    string formatPercent(double num, double den)    const;
    string buildBar(double ratio, int width)        const;
    void   printDivider(char c = '-', int w = 50)  const;
    void   printRow(const string& label, const string& value, int w = 50) const;
    string betTypeToString(RouletteBetType bt)      const;

public:
    explicit RouletteStats(double startingBankroll);

    void recordRound(const RouletteRoundSummary& summary);
    void displayStats() const;

    int    getTotalRounds()        const;
    int    getTotalWins()          const;
    int    getTotalLosses()        const;
    int    getColorBets()          const;
    int    getColorWins()          const;
    int    getNumberBets()         const;
    int    getNumberWins()         const;
    int    getBothBets()           const;
    int    getBothWins()           const;
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
