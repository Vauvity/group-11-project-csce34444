/*
    Name:       Prayush Panta
    UID:        PP1008
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444 Software Engineering
    Instructor: Bahareh M. Dorri

    Bankroll — Main gamble money tracker.

    Usage:
      - SessionStats owns one Bankroll instance.
      - Each game receives a Bankroll& in its constructor.
      - Games call withdraw() before a round and deposit() after payout.
      - validateBalance() can be called after any transaction to confirm
        the balance is consistent and non-negative.
*/

#ifndef BANKROLL_H
#define BANKROLL_H

#include <string>

using std::string;

class Bankroll
{
private:
    double balance;
    double startingBalance;
    double peakBalance;
    double lowestBalance;

    void updateTracking();

public:
    explicit Bankroll(double startingAmount);

    //  Core transactions 
    // Called by a game before a round begins (player places bet).
    // Returns false if the amount is invalid or exceeds balance.
    bool withdraw(double amount);

    // Called by a game after a round resolves (payout returned to player).
    void deposit(double amount);

    //  Validation 
    // Call after each round to confirm balance integrity.
    // Returns true if balance >= 0 and is internally consistent.
    bool validateBalance() const;

    //  Getters 
    double getBalance()         const;
    double getStartingBalance() const;
    double getNetGainLoss()     const;
    double getPeakBalance()     const;
    double getLowestBalance()   const;
    bool   isBroke()            const;

    //  Display 
    void printSummary() const;
};

#endif
