#ifndef SESSIONSTATS_H
#define SESSIONSTATS_H

#include <chrono>
#include "Bankroll.h"
#include "BlackjackStats.h"
#include "SlotsStats.h"
#include "RouletteStats.h"
#include "../blackjack/BlackjackTypes.h"
#include "../slots/SlotTypes.h"

using std::chrono::steady_clock;
using std::chrono::time_point;

class SessionStats
{
public:
    explicit SessionStats(double startingBalance = 1000.0);

    void startSession(double startingBalance);
    void endSession();
    double getSessionDuration() const;

    void recordBlackjackRound(const BlackjackRoundSummary& summary);
    void recordSlotsRound(const SlotsSummary& summary);
    void recordRouletteRound(const RouletteRoundSummary& summary, double endingBalance);
    void syncCurrentBalance(double balance);

    double getCurrentBalance() const;
    double getNetGainLoss() const;
    double getPeakBalance() const;
    double getLowestBalance() const;
    double getStartingBalance() const;

    int getTotalRounds() const;
    int getGamesPlayed() const;
    bool hasPlayedBlackjack() const;
    bool hasPlayedSlots() const;
    bool hasPlayedRoulette() const;
    bool isSessionStarted() const;

    const BlackjackStats& getBlackjackStats() const;
    const SlotsStats& getSlotsStats() const;
    const RouletteStats& getRouletteStats() const;

private:
    Bankroll bankroll;
    int totalRoundsAllGames;
    int gamesPlayed;
    bool playedBlackjack;
    bool playedSlots;
    bool playedRoulette;
    BlackjackStats blackjackStats;
    SlotsStats slotsStats;
    RouletteStats rouletteStats;
    time_point<steady_clock> sessionStart;
    bool sessionStarted;
};

#endif
