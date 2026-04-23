#include "Bankroll.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cmath>

using std::cout;
using std::fixed;
using std::setprecision;

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

void Bankroll::updateTracking()
{
    peakBalance = std::max(peakBalance, balance);
    lowestBalance = std::min(lowestBalance, balance);
}

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

void Bankroll::deposit(double amount)
{
    if (amount < 0.0)
    {
        lastError = ErrorCode::InvalidAmount;
        return;
    }

    balance += amount;
    updateTracking();
    lastError = ErrorCode::None;
}

void Bankroll::applyNetChange(double amount)
{
    balance += amount;
    updateTracking();

    if (balance < 0.0)
        lastError = ErrorCode::NegativeBalance;
    else
        lastError = ErrorCode::None;
}

void Bankroll::syncToBalance(double newBalance)
{
    balance = newBalance;
    updateTracking();

    if (balance < 0.0)
        lastError = ErrorCode::NegativeBalance;
    else
        lastError = ErrorCode::None;
}

void Bankroll::reset(double newStartingAmount)
{
    if (newStartingAmount <= 0.0)
    {
        lastError = ErrorCode::InvalidAmount;
        return;
    }

    startingBalance = newStartingAmount;
    balance = newStartingAmount;
    peakBalance = newStartingAmount;
    lowestBalance = newStartingAmount;
    lastError = ErrorCode::None;
}

bool Bankroll::validateBalance() const
{
    return balance >= 0.0;
}

Bankroll::ErrorCode Bankroll::getLastError() const
{
    return lastError;
}

std::string Bankroll::getLastErrorMessage() const
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

double Bankroll::getBalance() const
{
    return balance;
}

double Bankroll::getStartingBalance() const
{
    return startingBalance;
}

double Bankroll::getNetGainLoss() const
{
    return balance - startingBalance;
}

double Bankroll::getPeakBalance() const
{
    return peakBalance;
}

double Bankroll::getLowestBalance() const
{
    return lowestBalance;
}

bool Bankroll::isBroke() const
{
    return balance <= 0.0;
}

void Bankroll::printSummary() const
{
    double net = getNetGainLoss();

    cout << "\n========== Bankroll Summary ==========\n";
    cout << fixed << setprecision(2);
    cout << "  Starting Balance : $" << startingBalance << "\n";
    cout << "  Current Balance  : $" << balance << "\n";
    cout << "  Peak Balance     : $" << peakBalance << "\n";
    cout << "  Lowest Balance   : $" << lowestBalance << "\n";

    if (net >= 0.0)
        cout << "  Net Gain / Loss  : +$" << net << "\n";
    else
        cout << "  Net Gain / Loss  : -$" << std::abs(net) << "\n";

    cout << "======================================\n";
}