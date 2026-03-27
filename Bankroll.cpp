/*
    Name:       Prayush Panta
    UID:        PP1008
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include "Bankroll.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using std::cout;
using std::fixed;
using std::setprecision;


//  Constructor

Bankroll::Bankroll(double startingAmount)
    : balance(startingAmount),
      startingBalance(startingAmount),
      peakBalance(startingAmount),
      lowestBalance(startingAmount)
{
    if (startingAmount <= 0.0)
    {
        throw std::invalid_argument("Starting bankroll must be greater than 0.");
    }
}


//  Internal helper — updates peak and lowest after any change

void Bankroll::updateTracking()
{
    peakBalance   = std::max(peakBalance,   balance);
    lowestBalance = std::min(lowestBalance, balance);
}


//  withdraw — called by a game when player places a bet

bool Bankroll::withdraw(double amount)
{
    if (amount <= 0.0)
    {
        cout << "[Bankroll] Withdrawal rejected: amount must be greater than 0.\n";
        return false;
    }

    if (amount > balance)
    {
        cout << "[Bankroll] Withdrawal rejected: insufficient funds.\n";
        return false;
    }

    balance -= amount;
    updateTracking();
    return true;
}


//  deposit — called by a game when payout is returned to player

void Bankroll::deposit(double amount)
{
    if (amount <= 0.0)
    {
        return;   // no-op for zero payouts (losses); games handle messaging
    }

    balance += amount;
    updateTracking();
}


//  validateBalance — call after each round to confirm integrity

bool Bankroll::validateBalance() const
{
    if (balance < 0.0)
    {
        cout << "[Bankroll] WARNING: balance is negative ($"
             << fixed << setprecision(2) << balance << "). "
             << "Possible accounting error in game logic.\n";
        return false;
    }

    return true;
}


//  Getters

double Bankroll::getBalance()         const { return balance; }
double Bankroll::getStartingBalance() const { return startingBalance; }
double Bankroll::getNetGainLoss()     const { return balance - startingBalance; }
double Bankroll::getPeakBalance()     const { return peakBalance; }
double Bankroll::getLowestBalance()   const { return lowestBalance; }
bool   Bankroll::isBroke()            const { return balance <= 0.0; }


//  printSummary

void Bankroll::printSummary() const
{
    double net = getNetGainLoss();

    cout << "\n========== Bankroll Summary ==========\n";
    cout << fixed << setprecision(2);
    cout << "  Starting Balance : $" << startingBalance << "\n";
    cout << "  Current Balance  : $" << balance         << "\n";
    cout << "  Peak Balance     : $" << peakBalance     << "\n";
    cout << "  Lowest Balance   : $" << lowestBalance   << "\n";

    if (net >= 0.0)
        cout << "  Net Gain / Loss  : +$" << net << "\n";
    else
        cout << "  Net Gain / Loss  : -$" << (-net) << "\n";

    cout << "======================================\n";
}
