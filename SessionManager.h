#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "SessionStats.h"

class SessionManager
{
private:
    SessionStats sessionStats;

public:
    explicit SessionManager(double startingBalance);

    // Session lifecycle
    void startSession();
    void endSession();

    // Game routing
    void playBlackjack();
    void playSlots();
    void playRoulette();

    // Display
    void displaySessionSummary() const;

    // Getters
    double getCurrentBalance() const;
    double getNetGainLoss() const;
    double getPeakBalance() const;
    double getLowestBalance() const;
    int    getTotalRounds() const;
    int    getGamesPlayed() const;
    double getSessionDuration() const;

    const SessionStats& getSessionStats() const;
};

#endif