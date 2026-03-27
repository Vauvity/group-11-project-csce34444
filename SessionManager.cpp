#include "SessionManager.h"

SessionManager::SessionManager(double startingBalance)
    : sessionStats(startingBalance)
{
}

void SessionManager::startSession()
{
    sessionStats.startSession();
}

void SessionManager::endSession()
{
    sessionStats.endSession();
}

void SessionManager::playBlackjack()
{
    sessionStats.playBlackjack();
}

void SessionManager::playSlots()
{
    sessionStats.playSlots();
}

void SessionManager::playRoulette()
{
    sessionStats.playRoulette();
}

void SessionManager::displaySessionSummary() const
{
    sessionStats.displaySessionSummary();
}

double SessionManager::getCurrentBalance() const
{
    return sessionStats.getCurrentBalance();
}

double SessionManager::getNetGainLoss() const
{
    return sessionStats.getNetGainLoss();
}

double SessionManager::getPeakBalance() const
{
    return sessionStats.getPeakBalance();
}

double SessionManager::getLowestBalance() const
{
    return sessionStats.getLowestBalance();
}

int SessionManager::getTotalRounds() const
{
    return sessionStats.getTotalRounds();
}

int SessionManager::getGamesPlayed() const
{
    return sessionStats.getGamesPlayed();
}

double SessionManager::getSessionDuration() const
{
    return sessionStats.getSessionDuration();
}

const SessionStats& SessionManager::getSessionStats() const
{
    return sessionStats;
}