/*
    Name:       Prayush Panta
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include "RouletteStats.h"
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

RouletteStats::RouletteStats(double startBankroll)
    : totalRounds(0), totalWins(0), totalLosses(0),
      colorBets(0), colorWins(0), numberBets(0), numberWins(0),
      bothBets(0), bothWins(0),
      startingBankroll(startBankroll), currentBankroll(startBankroll),
      totalAmountBet(0.0), totalPayoutReceived(0.0),
      biggestWin(0.0), biggestLoss(0.0),
      peakBankroll(startBankroll), lowestBankroll(startBankroll),
      currentStreak(0), longestWinStreak(0), longestLossStreak(0)
{
}

void RouletteStats::recordRound(const RouletteRoundSummary& summary)
{
    totalRounds++;

    if (summary.playerWon)
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

    switch (summary.betType)
    {
        case RouletteBetType::Color:
            colorBets++;  if (summary.playerWon) colorWins++;  break;
        case RouletteBetType::Number:
            numberBets++; if (summary.playerWon) numberWins++; break;
        case RouletteBetType::Both:
            bothBets++;   if (summary.playerWon) bothWins++;   break;
        default: break;
    }

    totalAmountBet      += summary.betAmount;
    totalPayoutReceived += summary.payoutAmount;
    currentBankroll      = summary.endingBankroll;

    if (summary.netChange > 0.0)
        biggestWin  = std::max(biggestWin,  summary.netChange);
    else if (summary.netChange < 0.0)
        biggestLoss = std::max(biggestLoss, std::abs(summary.netChange));

    peakBankroll   = std::max(peakBankroll,   currentBankroll);
    lowestBankroll = std::min(lowestBankroll, currentBankroll);

    RoundResult r;
    r.roundNumber   = summary.roundNumber;
    r.betType       = betTypeToString(summary.betType);
    r.outcome       = summary.playerWon ? "WIN" : "LOSS";
    r.netChange     = summary.netChange;
    r.bankrollAfter = summary.endingBankroll;
    history.push_back(r);
    if (history.size() > 10) history.erase(history.begin());
}

void RouletteStats::displayStats() const
{
    const int W = 50;

    cout << endl;
    printDivider('=', W);
    cout << setw((W + 22) / 2) << right
         << "* GALACTIC CASINO  --  ROULETTE STATS *" << endl;
    printDivider('=', W);

    cout << " SESSION OVERVIEW" << endl;
    printDivider('-', W);
    printRow("Rounds Played",     std::to_string(totalRounds),                      W);
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
    printRow("Wins",     std::to_string(totalWins)   + "  " + formatPercent(totalWins,   totalRounds), W);
    printRow("Losses",   std::to_string(totalLosses) + "  " + formatPercent(totalLosses, totalRounds), W);
    printRow("Win Rate", formatPercent(totalWins, totalRounds), W);

    if (totalRounds > 0)
        cout << "  [" << buildBar((double)totalWins / totalRounds, W - 6) << "]" << endl;

    cout << endl << " BET TYPE BREAKDOWN" << endl;
    printDivider('-', W);
    printRow("Color Bets",   std::to_string(colorBets),                             W);
    if (colorBets > 0)
        printRow("  Color Wins", std::to_string(colorWins) + "  " +
                                 formatPercent(colorWins, colorBets),               W);
    printRow("Number Bets",  std::to_string(numberBets),                            W);
    if (numberBets > 0)
        printRow("  Number Wins", std::to_string(numberWins) + "  " +
                                  formatPercent(numberWins, numberBets),            W);
    printRow("Both Bets",    std::to_string(bothBets),                              W);
    if (bothBets > 0)
        printRow("  Both Wins",  std::to_string(bothWins) + "  " +
                                 formatPercent(bothWins, bothBets),                 W);

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

    cout << endl << " LAST " << history.size() << " ROUNDS" << endl;
    printDivider('-', W);
    cout << left << setw(8) << "  Round" << setw(10) << "Bet Type"
         << setw(8) << "Result" << setw(12) << "Net" << setw(12) << "Bankroll" << endl;
    printDivider('-', W);

    for (const RoundResult& r : history)
    {
        cout << left
             << setw(8)  << ("  #" + std::to_string(r.roundNumber))
             << setw(10) << r.betType
             << setw(8)  << r.outcome
             << setw(12) << formatMoney(r.netChange)
             << setw(12) << formatMoney(r.bankrollAfter)
             << endl;
    }

    printDivider('=', W);
    cout << endl;
}

string RouletteStats::betTypeToString(RouletteBetType bt) const
{
    switch (bt)
    {
        case RouletteBetType::Color:  return "Color";
        case RouletteBetType::Number: return "Number";
        case RouletteBetType::Both:   return "Both";
        default:                      return "---";
    }
}

string RouletteStats::formatMoney(double amount) const
{
    ostringstream out;
    if (amount >= 0) out << "+$" << fixed << setprecision(2) << amount;
    else             out << "-$" << fixed << setprecision(2) << std::abs(amount);
    return out.str();
}

string RouletteStats::formatPercent(double n, double d) const
{
    if (d <= 0) return "(0.0%)";
    ostringstream out;
    out << "(" << fixed << setprecision(1) << (n / d * 100.0) << "%)";
    return out.str();
}

string RouletteStats::buildBar(double ratio, int width) const
{
    int filled = std::max(0, std::min(static_cast<int>(ratio * width), width));
    return string(filled, '#') + string(width - filled, '.');
}

void RouletteStats::printDivider(char c, int w) const { cout << string(w, c) << endl; }

void RouletteStats::printRow(const string& label, const string& value, int w) const
{
    int gap = w - 2 - (int)label.size() - (int)value.size();
    if (gap < 1) gap = 1;
    cout << "  " << label << string(gap, '.') << value << endl;
}

int    RouletteStats::getTotalRounds()        const { return totalRounds; }
int    RouletteStats::getTotalWins()          const { return totalWins; }
int    RouletteStats::getTotalLosses()        const { return totalLosses; }
int    RouletteStats::getColorBets()          const { return colorBets; }
int    RouletteStats::getColorWins()          const { return colorWins; }
int    RouletteStats::getNumberBets()         const { return numberBets; }
int    RouletteStats::getNumberWins()         const { return numberWins; }
int    RouletteStats::getBothBets()           const { return bothBets; }
int    RouletteStats::getBothWins()           const { return bothWins; }
int    RouletteStats::getLongestWinStreak()   const { return longestWinStreak; }
int    RouletteStats::getLongestLossStreak()  const { return longestLossStreak; }
int    RouletteStats::getCurrentStreak()      const { return currentStreak; }
double RouletteStats::getStartingBankroll()   const { return startingBankroll; }
double RouletteStats::getCurrentBankroll()    const { return currentBankroll; }
double RouletteStats::getNetProfit()          const { return currentBankroll - startingBankroll; }
double RouletteStats::getTotalAmountBet()     const { return totalAmountBet; }
double RouletteStats::getTotalPayoutReceived()const { return totalPayoutReceived; }
double RouletteStats::getBiggestWin()         const { return biggestWin; }
double RouletteStats::getBiggestLoss()        const { return biggestLoss; }
double RouletteStats::getPeakBankroll()       const { return peakBankroll; }
double RouletteStats::getLowestBankroll()     const { return lowestBankroll; }
double RouletteStats::getWinRate()            const { return totalRounds > 0 ? (double)totalWins / totalRounds : 0.0; }
double RouletteStats::getROI()               const { return totalAmountBet > 0 ? (currentBankroll - startingBankroll) / totalAmountBet : 0.0; }
