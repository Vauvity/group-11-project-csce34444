/*
    Name:       Prayush Panta
    UID:        PP1008
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444 Software Engineering
    Instructor: Bahareh M. Dorri

    main.cpp — Casino entry point.
    SessionStats owns the Bankroll. All game runners receive it
    by reference so balance stays centralized across all games.
*/

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "SessionStats.h"

using std::cout;
using std::cin;
using std::string;
using std::fixed;
using std::setprecision;
using std::numeric_limits;
using std::streamsize;


//  Forward declarations

double promptStartingBankroll();
int    promptMenuChoice();
void   showMenu(double balance);


//  Main

int main()
{
    cout << "========================================\n";
    cout << "      Welcome to Galactic Casino!\n";
    cout << "========================================\n";

    double startingBalance = promptStartingBankroll();

    SessionStats session(startingBalance);
    session.startSession();

    bool running = true;

    while (running)
    {
        if (session.getCurrentBalance() <= 0.0)
        {
            cout << "\nYou're out of money! Session over.\n";
            break;
        }

        showMenu(session.getCurrentBalance());
        int choice = promptMenuChoice();

        switch (choice)
        {
            case 1:
                session.playBlackjack();
                break;

            case 2:
                session.playSlots();       // placeholder until Sprint 2
                break;

            case 3:
                session.playRoulette();    // placeholder until Sprint 2
                break;

            case 4:
                session.displaySessionSummary();
                break;

            case 5:
                cout << "\nCashing out...\n";
                running = false;
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    session.endSession();
    session.displaySessionSummary();

    cout << "\nThanks for playing at Galactic Casino!\n";
    return 0;
}


//  Helpers

double promptStartingBankroll()
{
    double bankroll;
    while (true)
    {
        cout << "Enter your starting bankroll: $";
        cin >> bankroll;

        if (cin.fail() || bankroll <= 0.0)
        {
            cout << "Please enter a valid amount greater than 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return bankroll;
        }
    }
}

void showMenu(double balance)
{
    cout << "\n========================================\n";
    cout << "  Balance: $" << fixed << setprecision(2) << balance << "\n";
    cout << "----------------------------------------\n";
    cout << "  1. Blackjack\n";
    cout << "  2. Slots        \n";
    cout << "  3. Roulette     \n";
    cout << "  4. View Session Summary\n";
    cout << "  5. Cash Out & Exit\n";
    cout << "========================================\n";
}

int promptMenuChoice()
{
    int choice;
    while (true)
    {
        cout << "Choice: ";
        if (cin >> choice)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number.\n";
    }
}
