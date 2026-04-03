/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include "SlotsStats.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::ostringstream;
using std::string;

SlotsStats::SlotsStats(double startBankroll)
    : totalSpins(0), totalWins(0), totalLosses(0),
      startingBankroll(startBankroll), currentBankroll(startBankroll),
      totalAmountBet(0.0), totalPayoutReceived(0.0),
      biggestWin(0.0), biggestLoss(0.0),
      peakBankroll(startBankroll), lowestBankroll(startBankroll),
      currentStreak(0), longestWinStreak(0), longestLossStreak(0)
{
}

void SlotsStats::recordRound(const SlotsSummary& summary)
{
    totalSpins++;

    if (summary.won)
    {
        totalWins++;
        currentStreak    = (currentStreak > 0) ? currentStreak + 1 : 1;
        longestWinStreak = std::max(longestWinStreak, currentStreak);
    }
    else
    {
        totalLosses++;
        currentStreak     = (currentStreak < 0) ? currentStreak - 1 : -1;
        longestLossStreak = std::max(longestLossStreak, std::abs(currentStreak));
    }

    totalAmountBet      += summary.betMade;
    totalPayoutReceived += summary.payoutAmount;
    currentBankroll      = summary.endingBankroll;

    if (summary.netChange > 0.0)
        biggestWin  = std::max(biggestWin,  summary.netChange);
    else if (summary.netChange < 0.0)
        biggestLoss = std::max(biggestLoss, std::abs(summary.netChange));

    peakBankroll   = std::max(peakBankroll,   currentBankroll);
    lowestBankroll = std::min(lowestBankroll, currentBankroll);

    SpinResult r;
    r.spinNumber   = summary.spinNumber;
    r.outcome      = summary.won ? "WIN" : "LOSS";
    r.netChange    = summary.netChange;
    r.bankrollAfter = summary.endingBankroll;
    history.push_back(r);
    if (history.size() > 10) history.erase(history.begin());
}

void SlotsStats::displayStats() const
{
    const int W = 50;

    cout << endl;
    printDivider('=', W);
    cout << setw((W + 20) / 2) << right
         << "* GALACTIC CASINO  --  SLOTS STATS *" << endl;
    printDivider('=', W);

    cout << " SESSION OVERVIEW" << endl;
    printDivider('-', W);
    printRow("Spins Played",      std::to_string(totalSpins),                       W);
    printRow("Starting Bankroll", formatMoney(startingBankroll),                    W);
    printRow("Current Bankroll",  formatMoney(currentBankroll),                     W);
    printRow("Net Profit / Loss", formatMoney(currentBankroll - startingBankroll),  W);
    printRow("Peak Bankroll",     formatMoney(peakBankroll),                        W);
    printRow("Lowest Bankroll",   formatMoney(lowestBankroll),                      W);
    printRow("Total Wagered",     formatMoney(totalAmountBet),                      W);
    printRow("ROI",               formatPercent(currentBankroll - startingBankroll,
                                                totalAmountBet),                    W);

    cout << endl << " WIN / LOSS BREAKDOWN" << endl;
    printDivider('-', W);
    printRow("Wins",     std::to_string(totalWins)   + "  " + formatPercent(totalWins,   totalSpins), W);
    printRow("Losses",   std::to_string(totalLosses) + "  " + formatPercent(totalLosses, totalSpins), W);
    printRow("Win Rate", formatPercent(totalWins, totalSpins), W);

    if (totalSpins > 0)
        cout << "  [" << buildBar((double)totalWins / totalSpins, W - 6) << "]" << endl;

    cout << endl << " STREAKS & RECORDS" << endl;
    printDivider('-', W);

    string streakStr;
    if      (currentStreak > 0) streakStr = "+" + std::to_string(currentStreak) + " (winning)";
    else if (currentStreak < 0) streakStr =       std::to_string(currentStreak) + " (losing)";
    else                        streakStr = "0 (neutral)";

    printRow("Current Streak",      streakStr,                         W);
    printRow("Longest Win Streak",  std::to_string(longestWinStreak),  W);
    printRow("Longest Loss Streak", std::to_string(longestLossStreak), W);
    printRow("Biggest Single Win",  formatMoney(biggestWin),           W);
    printRow("Biggest Single Loss", formatMoney(biggestLoss),          W);

    cout << endl << " LAST " << history.size() << " SPINS" << endl;
    printDivider('-', W);
    cout << left << setw(8) << "  Spin" << setw(8) << "Result"
         << setw(12) << "Net" << setw(14) << "Bankroll" << endl;
    printDivider('-', W);

    for (const SpinResult& r : history)
    {
        cout << left
             << setw(8)  << ("  #" + std::to_string(r.spinNumber))
             << setw(8)  << r.outcome
             << setw(12) << formatMoney(r.netChange)
             << setw(14) << formatMoney(r.bankrollAfter)
             << endl;
    }

    printDivider('=', W);
    cout << endl;
}

string SlotsStats::formatMoney(double amount) const
{
    ostringstream out;
    if (amount >= 0) out << "+$" << fixed << setprecision(2) << amount;
    else             out << "-$" << fixed << setprecision(2) << std::abs(amount);
    return out.str();
}

string SlotsStats::formatPercent(double n, double d) const
{
    if (d <= 0) return "(0.0%)";
    ostringstream out;
    out << "(" << fixed << setprecision(1) << (n / d * 100.0) << "%)";
    return out.str();
}

string SlotsStats::buildBar(double ratio, int width) const
{
    int filled = std::max(0, std::min(static_cast<int>(ratio * width), width));
    return string(filled, '#') + string(width - filled, '.');
}

void SlotsStats::printDivider(char c, int w) const { cout << string(w, c) << endl; }

void SlotsStats::printRow(const string& label, const string& value, int w) const
{
    int gap = w - 2 - (int)label.size() - (int)value.size();
    if (gap < 1) gap = 1;
    cout << "  " << label << string(gap, '.') << value << endl;
}

int    SlotsStats::getTotalSpins()         const { return totalSpins; }
int    SlotsStats::getTotalWins()          const { return totalWins; }
int    SlotsStats::getTotalLosses()        const { return totalLosses; }
int    SlotsStats::getLongestWinStreak()   const { return longestWinStreak; }
int    SlotsStats::getLongestLossStreak()  const { return longestLossStreak; }
int    SlotsStats::getCurrentStreak()      const { return currentStreak; }
double SlotsStats::getStartingBankroll()   const { return startingBankroll; }
double SlotsStats::getCurrentBankroll()    const { return currentBankroll; }
double SlotsStats::getNetProfit()          const { return currentBankroll - startingBankroll; }
double SlotsStats::getTotalAmountBet()     const { return totalAmountBet; }
double SlotsStats::getTotalPayoutReceived()const { return totalPayoutReceived; }
double SlotsStats::getBiggestWin()         const { return biggestWin; }
double SlotsStats::getBiggestLoss()        const { return biggestLoss; }
double SlotsStats::getPeakBankroll()       const { return peakBankroll; }
double SlotsStats::getLowestBankroll()     const { return lowestBankroll; }
double SlotsStats::getWinRate()            const { return totalSpins > 0 ? (double)totalWins / totalSpins : 0.0; }
double SlotsStats::getROI()               const { return totalAmountBet > 0 ? (currentBankroll - startingBankroll) / totalAmountBet : 0.0; }
