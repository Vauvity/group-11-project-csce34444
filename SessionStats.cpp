/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include "SessionStats.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::fixed;
using std::setprecision;
using std::setw;
using std::right;


//  Constructor

SessionStats::SessionStats(double startBalance)
    : bankroll(startBalance),
      totalRoundsAllGames(0),
      gamesPlayed(0),
      playedBlackjack(false),
      playedSlots(false),
      playedRoulette(false),
      blackjackStats(startBalance),
      slotsStats(startBalance),
      rouletteStats(startBalance),
      sessionStarted(false)
{
}


//  Session lifecycle

void SessionStats::startSession()
{
    sessionStart   = steady_clock::now();
    sessionStarted = true;
}

void SessionStats::endSession()
{
    sessionStarted = false;
}

double SessionStats::getSessionDuration() const
{
    if (!sessionStarted) return 0.0;
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        steady_clock::now() - sessionStart);
    return static_cast<double>(elapsed.count());
}


//  Record methods

void SessionStats::recordBlackjackRound(const BlackjackRoundSummary& summary)
{
    if (!playedBlackjack)
    {
        playedBlackjack = true;
        gamesPlayed++;
    }
    blackjackStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.validateBalance();
}

void SessionStats::recordSlotsRound(const SlotsSummary& summary)
{
    if (!playedSlots)
    {
        playedSlots = true;
        gamesPlayed++;
    }
    slotsStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.validateBalance();
}

void SessionStats::recordRouletteRound(const RouletteRoundSummary& summary)
{
    if (!playedRoulette)
    {
        playedRoulette = true;
        gamesPlayed++;
    }
    rouletteStats.recordRound(summary);
    totalRoundsAllGames++;
    bankroll.validateBalance();
}


//  Display methods

void SessionStats::displayOverallStats() const
{
    const int W = 52;

    double net = bankroll.getNetGainLoss();
    double dur = const_cast<SessionStats*>(this)->getSessionDuration();

    cout << endl;
    printDivider('=', W);
    cout << setw((W + 26) / 2) << right
         << "* GALACTIC CASINO  --  SESSION SUMMARY *\n";
    printDivider('=', W);

    cout << " BANKROLL\n";
    printDivider('-', W);
    printRow("Starting Balance", formatMoney(bankroll.getStartingBalance()), W);
    printRow("Final Balance",    formatMoney(bankroll.getBalance()),         W);
    printRow("Net Gain / Loss",  formatMoney(net),                          W);
    printRow("Peak Balance",     formatMoney(bankroll.getPeakBalance()),     W);
    printRow("Lowest Balance",   formatMoney(bankroll.getLowestBalance()),   W);

    cout << "\n SESSION\n";
    printDivider('-', W);
    printRow("Session Duration", formatDuration(dur),                 W);
    printRow("Total Rounds",     std::to_string(totalRoundsAllGames), W);
    printRow("Games Played",     std::to_string(gamesPlayed),         W);

    cout << "\n PER-GAME SUMMARY\n";
    printDivider('-', W);

    if (playedBlackjack)
    {
        cout << "  Blackjack\n";
        printRow("    Hands Played",  std::to_string(blackjackStats.getTotalRounds()),       W);
        printRow("    Wins",          std::to_string(blackjackStats.getTotalWins()),         W);
        printRow("    Losses",        std::to_string(blackjackStats.getTotalLosses()),       W);
        printRow("    Pushes",        std::to_string(blackjackStats.getTotalPushes()),       W);
        printRow("    Blackjacks",    std::to_string(blackjackStats.getTotalBlackjacks()),   W);
        printRow("    Win Streak",    std::to_string(blackjackStats.getLongestWinStreak()),  W);
        printRow("    Loss Streak",   std::to_string(blackjackStats.getLongestLossStreak()), W);
        ostringstream wr;
        wr << fixed << setprecision(1) << blackjackStats.getWinRate() * 100.0 << "%";
        printRow("    Win Rate",      wr.str(),                                              W);
        printRow("    Net",           formatMoney(blackjackStats.getNetProfit()),            W);
    }

    if (playedSlots)
    {
        cout << "  Slots\n";
        printRow("    Spins Played",  std::to_string(slotsStats.getTotalSpins()),        W);
        printRow("    Wins",          std::to_string(slotsStats.getTotalWins()),         W);
        printRow("    Losses",        std::to_string(slotsStats.getTotalLosses()),       W);
        printRow("    Win Streak",    std::to_string(slotsStats.getLongestWinStreak()),  W);
        printRow("    Loss Streak",   std::to_string(slotsStats.getLongestLossStreak()), W);
        ostringstream wr;
        wr << fixed << setprecision(1) << slotsStats.getWinRate() * 100.0 << "%";
        printRow("    Win Rate",      wr.str(),                                          W);
        printRow("    Net",           formatMoney(slotsStats.getNetProfit()),            W);
    }

    if (playedRoulette)
    {
        cout << "  Roulette\n";
        printRow("    Rounds Played", std::to_string(rouletteStats.getTotalRounds()),       W);
        printRow("    Wins",          std::to_string(rouletteStats.getTotalWins()),         W);
        printRow("    Losses",        std::to_string(rouletteStats.getTotalLosses()),       W);
        printRow("    Color Bets",    std::to_string(rouletteStats.getColorBets()),         W);
        printRow("    Number Bets",   std::to_string(rouletteStats.getNumberBets()),        W);
        printRow("    Both Bets",     std::to_string(rouletteStats.getBothBets()),          W);
        printRow("    Win Streak",    std::to_string(rouletteStats.getLongestWinStreak()),  W);
        printRow("    Loss Streak",   std::to_string(rouletteStats.getLongestLossStreak()), W);
        ostringstream wr;
        wr << fixed << setprecision(1) << rouletteStats.getWinRate() * 100.0 << "%";
        printRow("    Win Rate",      wr.str(),                                             W);
        printRow("    Net",           formatMoney(rouletteStats.getNetProfit()),            W);
    }

    printDivider('=', W);
    cout << endl;
}

void SessionStats::displayBlackjackStats() const { blackjackStats.displayStats(); }
void SessionStats::displaySlotsStats()     const { slotsStats.displayStats(); }
void SessionStats::displayRouletteStats()  const { rouletteStats.displayStats(); }

void SessionStats::displayAllStats() const
{
    displayOverallStats();
    if (playedBlackjack) displayBlackjackStats();
    if (playedSlots)     displaySlotsStats();
    if (playedRoulette)  displayRouletteStats();
}


//  Bankroll access

double   SessionStats::getCurrentBalance()  const { return bankroll.getBalance(); }
double   SessionStats::getNetGainLoss()     const { return bankroll.getNetGainLoss(); }
double   SessionStats::getPeakBalance()     const { return bankroll.getPeakBalance(); }
double   SessionStats::getLowestBalance()   const { return bankroll.getLowestBalance(); }
double   SessionStats::getStartingBalance() const { return bankroll.getStartingBalance(); }
Bankroll& SessionStats::getBankroll()             { return bankroll; }


//  Session counters

int  SessionStats::getTotalRounds()      const { return totalRoundsAllGames; }
int  SessionStats::getGamesPlayed()      const { return gamesPlayed; }
bool SessionStats::hasPlayedBlackjack()  const { return playedBlackjack; }
bool SessionStats::hasPlayedSlots()      const { return playedSlots; }
bool SessionStats::hasPlayedRoulette()   const { return playedRoulette; }


//  Per-game stats access

const BlackjackStats& SessionStats::getBlackjackStats() const { return blackjackStats; }
const SlotsStats&     SessionStats::getSlotsStats()     const { return slotsStats; }
const RouletteStats&  SessionStats::getRouletteStats()  const { return rouletteStats; }


//  Formatting helpers

string SessionStats::formatMoney(double amount) const
{
    ostringstream out;
    if (amount >= 0) out << "+$" << fixed << setprecision(2) << amount;
    else             out << "-$" << fixed << setprecision(2) << std::abs(amount);
    return out.str();
}

string SessionStats::formatDuration(double seconds) const
{
    ostringstream out;
    out << static_cast<int>(seconds) / 60 << "m "
        << static_cast<int>(seconds) % 60 << "s";
    return out.str();
}

void SessionStats::printDivider(char c, int width) const
{
    cout << string(width, c) << endl;
}

void SessionStats::printRow(const string& label, const string& value, int width) const
{
    int gap = width - 2 - (int)label.size() - (int)value.size();
    if (gap < 1) gap = 1;
    cout << "  " << label << string(gap, '.') << value << endl;
}
