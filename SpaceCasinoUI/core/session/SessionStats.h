/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Header for the SessionStats class, which manages session bankroll, duration, and cross-game statistics.
 */

#ifndef SESSIONSTATS_H
#define SESSIONSTATS_H

#include <string>
#include <chrono>
#include "Bankroll.h"
#include "BlackjackStats.h"
#include "SlotsStats.h"
#include "RouletteStats.h"

using std::string;
using std::chrono::steady_clock;
using std::chrono::time_point;

class SessionStats
{
private:
    //  Centralized bankroll 
    Bankroll bankroll;

    //  Cross-game session totals 
    int  totalRoundsAllGames;
    int  gamesPlayed;
    bool playedBlackjack;
    bool playedSlots;
    bool playedRoulette;

    //  Per-game stats modules 
    BlackjackStats blackjackStats;
    SlotsStats slotsStats;
    RouletteStats rouletteStats;

    //  Session timer 
    time_point<steady_clock> sessionStart;
    bool sessionStarted;

    //  Helpers 
    //  (Terminal format helpers removed)

public:
    explicit SessionStats(double startingBalance);

    //  Session lifecycle 
    void startSession();
    void endSession();

    //  (Terminal runners and display removed)

    //  Getters 
    double getCurrentBalance()  const { return bankroll.getBalance(); }
    double getNetGainLoss()     const { return bankroll.getNetGainLoss(); }
    double getPeakBalance()     const { return bankroll.getPeakBalance(); }
    double getLowestBalance()   const { return bankroll.getLowestBalance(); }
    int    getTotalRounds()     const { return totalRoundsAllGames; }
    int    getGamesPlayed()     const { return gamesPlayed; }
    double getSessionDuration() const;

    const BlackjackStats& getBlackjackStats() const { return blackjackStats; }
    const SlotsStats& getSlotsStats() const { return slotsStats; }
    const RouletteStats& getRouletteStats() const { return rouletteStats; }

    void recordBlackjackRound(const BlackjackRoundSummary& summary) {
        blackjackStats.recordRound(summary);
        totalRoundsAllGames++;
        if (!playedBlackjack) { playedBlackjack = true; gamesPlayed++; }
        bankroll.setBalance(summary.endingBankroll);
    }
    
    void recordSlotsRound(const SlotsRoundSummary& summary) {
        slotsStats.recordRound(summary);
        totalRoundsAllGames++;
        if (!playedSlots) { playedSlots = true; gamesPlayed++; }
        bankroll.deposit(summary.payoutAmount);
        bankroll.withdraw(summary.betAmount); // rough estimation for deposit/withdraw tracking if needed
    }
    
    void recordRouletteRound(const RouletteRoundSummary& summary) {
        rouletteStats.recordRound(summary);
        totalRoundsAllGames++;
        if (!playedRoulette) { playedRoulette = true; gamesPlayed++; }
        bankroll.deposit(summary.payoutAmount);
        bankroll.withdraw(summary.betAmount);
    }
    
    Bankroll& getBankroll() { return bankroll; }
    const Bankroll& getBankroll() const { return bankroll; }
};

#endif
