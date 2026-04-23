#pragma once
#include <string>

class Bankroll
{
public:
    enum class ErrorCode
    {
        None,
        InvalidAmount,
        InsufficientFunds,
        NegativeBalance
    };

    explicit Bankroll(double startingAmount = 1000.0);

    bool withdraw(double amount);
    void deposit(double amount);
    void applyNetChange(double amount);
    void syncToBalance(double newBalance);
    void reset(double startingAmount);

    bool validateBalance() const;

    ErrorCode getLastError() const;
    std::string getLastErrorMessage() const;

    double getBalance() const;
    double getStartingBalance() const;
    double getNetGainLoss() const;
    double getPeakBalance() const;
    double getLowestBalance() const;
    bool isBroke() const;

    void printSummary() const;

private:
    double balance;
    double startingBalance;
    double peakBalance;
    double lowestBalance;
    ErrorCode lastError;

    void updateTracking();
};