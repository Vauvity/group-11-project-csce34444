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
      lowestBalance(startingAmount),
      lastError(ErrorCode::None)
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
        lastError = ErrorCode::InvalidAmount;
        return false;
    }

    if (amount > balance)
    {
        lastError = ErrorCode::InsufficientFunds;
        return false;
    }

    balance -= amount;
    updateTracking();
    lastError = ErrorCode::None;
    return true;
}


//  deposit — called by a game when payout is returned to player

void Bankroll::deposit(double amount)
{
    if (amount <= 0.0)
    {
        lastError = ErrorCode::InvalidAmount;
        return;   // no-op for zero payouts (losses); games handle messaging
    }

    balance += amount;
    updateTracking();
    lastError = ErrorCode::None;
}


//  validateBalance — call after each round to confirm integrity

bool Bankroll::validateBalance() const
{
    if (balance < 0.0)
    {
        return false;
    }

    return true;
}

Bankroll::ErrorCode Bankroll::getLastError() const
{
    return lastError;
}

string Bankroll::getLastErrorMessage() const
{
    switch (lastError)
    {
        case ErrorCode::None:
            return "";
        case ErrorCode::InvalidAmount:
            return "Amount must be greater than 0.";
        case ErrorCode::InsufficientFunds:
            return "Insufficient funds.";
        case ErrorCode::NegativeBalance:
            return "Balance is negative. Possible accounting error.";
        default:
            return "Unknown bankroll error.";
    }
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
