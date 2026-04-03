/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri

    SessionStats.h
    Pure stats coordinator. No terminal I/O, no game loops.

    Owns the shared Bankroll for the session.
    SessionManager calls the record*Round() methods after each game action.
    The UI stats button calls display*Stats() methods.
*/

#ifndef SESSIONSTATS_H
#define SESSIONSTATS_H

#include <string>
#include <chrono>
#include "Bankroll.h"
#include "BlackjackStats.h"
#include "SlotsStats.h"
#include "RouletteStats.h"
#include "BlackjackTypes.h"
#include "SlotTypes.h"
#include "RouletteTypes.h"

using std::string;
using std::chrono::steady_clock;
using std::chrono::time_point;

class SessionStats
{
public:
    explicit SessionStats(double startingBalance);

    //  Session lifecycle
    void startSession();
    void endSession();
    double getSessionDuration() const;

    //  Record methods — called by SessionManager after each round
    void recordBlackjackRound(const BlackjackRoundSummary& summary);
    void recordSlotsRound    (const SlotsSummary&          summary);
    void recordRouletteRound (const RouletteRoundSummary&  summary);

    //  Display methods — triggered by UI stats button
    void displayOverallStats()   const;
    void displayBlackjackStats() const;
    void displaySlotsStats()     const;
    void displayRouletteStats()  const;
    void displayAllStats()       const;  // overall + all per-game panels

    //  Bankroll access — SessionManager reads these for UI display
    double getCurrentBalance()  const;
    double getNetGainLoss()     const;
    double getPeakBalance()     const;
    double getLowestBalance()   const;
    double getStartingBalance() const;

    //  Session-level counters
    int getTotalRounds()  const;
    int getGamesPlayed()  const;
    bool hasPlayedBlackjack() const;
    bool hasPlayedSlots()     const;
    bool hasPlayedRoulette()  const;

    //  Per-game stats access — for UI to read individual values
    const BlackjackStats& getBlackjackStats() const;
    const SlotsStats&     getSlotsStats()     const;
    const RouletteStats&  getRouletteStats()  const;

    //  Bankroll reference — passed into game constructors by SessionManager
    Bankroll& getBankroll();

private:
    Bankroll bankroll;

    int  totalRoundsAllGames;
    int  gamesPlayed;
    bool playedBlackjack;
    bool playedSlots;
    bool playedRoulette;

    BlackjackStats blackjackStats;
    SlotsStats     slotsStats;
    RouletteStats  rouletteStats;

    time_point<steady_clock> sessionStart;
    bool sessionStarted;

    //  Formatting helpers
    string formatMoney(double amount)    const;
    string formatDuration(double secs)   const;
    void   printDivider(char c = '-', int width = 52) const;
    void   printRow(const string& label, const string& value, int width = 52) const;
};

#endif
