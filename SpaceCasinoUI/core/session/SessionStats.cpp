#include "SessionStats.h"

SessionStats::SessionStats(double startingBalance)
    : bankroll(startingBalance), totalRoundsAllGames(0), gamesPlayed(0),
      playedBlackjack(false), playedSlots(false), playedRoulette(false),
      blackjackStats(startingBalance), slotsStats(startingBalance), rouletteStats(startingBalance),
      sessionStarted(false) {}

void SessionStats::startSession(double startingBalance)
{
    bankroll.reset(startingBalance);
    totalRoundsAllGames = 0;
    gamesPlayed = 0;
    playedBlackjack = false;
    playedSlots = false;
    playedRoulette = false;
    blackjackStats = BlackjackStats(startingBalance);
    slotsStats = SlotsStats(startingBalance);
    rouletteStats = RouletteStats(startingBalance);
    sessionStart = steady_clock::now();
    sessionStarted = true;
}

void SessionStats::endSession() { sessionStarted = false; }

double SessionStats::getSessionDuration() const
{
    if (!sessionStarted) return 0.0;
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(steady_clock::now() - sessionStart);
    return static_cast<double>(elapsed.count());
}

void SessionStats::recordBlackjackRound(const BlackjackRoundSummary& summary)
{
    if (!playedBlackjack) { playedBlackjack = true; gamesPlayed++; }
    blackjackStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.syncToBalance(summary.endingBankroll);
}

void SessionStats::recordSlotsRound(const SlotsSummary& summary)
{
    if (!playedSlots) { playedSlots = true; gamesPlayed++; }
    slotsStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.syncToBalance(summary.endingBankroll);
}

void SessionStats::recordRouletteRound(const RouletteRoundSummary& summary, double endingBalance)
{
    if (!playedRoulette) { playedRoulette = true; gamesPlayed++; }
    rouletteStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.syncToBalance(endingBalance);
}

void SessionStats::syncCurrentBalance(double balance) { bankroll.syncToBalance(balance); }
double SessionStats::getCurrentBalance() const { return bankroll.getBalance(); }
double SessionStats::getNetGainLoss() const { return bankroll.getNetGainLoss(); }
double SessionStats::getPeakBalance() const { return bankroll.getPeakBalance(); }
double SessionStats::getLowestBalance() const { return bankroll.getLowestBalance(); }
double SessionStats::getStartingBalance() const { return bankroll.getStartingBalance(); }
int SessionStats::getTotalRounds() const { return totalRoundsAllGames; }
int SessionStats::getGamesPlayed() const { return gamesPlayed; }
bool SessionStats::hasPlayedBlackjack() const { return playedBlackjack; }
bool SessionStats::hasPlayedSlots() const { return playedSlots; }
bool SessionStats::hasPlayedRoulette() const { return playedRoulette; }
bool SessionStats::isSessionStarted() const { return sessionStarted; }
const BlackjackStats& SessionStats::getBlackjackStats() const { return blackjackStats; }
const SlotsStats& SessionStats::getSlotsStats() const { return slotsStats; }
const RouletteStats& SessionStats::getRouletteStats() const { return rouletteStats; }
