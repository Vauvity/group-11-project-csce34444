#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <fstream>
#include "BlackjackGame.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

double promptStartingBankroll();
double promptBetAmount(const BlackjackGame& game);
string promptPlayerAction(const BlackjackGame& game);
void showTableState(const BlackjackGame& game);
void showRoundLog(const BlackjackGame& game);
string getDealerVisibleHand(const BlackjackGame& game);
bool promptPlayAgain();

void writeRoundLogToFile(const BlackjackGame& game)
{
    std::ofstream logFile("blackjack_log.txt", std::ios::app);

    std::vector<std::string> roundLog = game.getRoundLog();

    for (const std::string& entry : roundLog)
    {
        logFile << entry << "\n";
    }

    logFile << "\n";

    logFile.close();
}

int main()
{
    cout << "========================================" << endl;
    cout << "     Welcome to Terminal Blackjack" << endl;
    cout << "========================================" << endl;

    double startingBankroll = promptStartingBankroll();
    BlackjackGame game(startingBankroll);

    bool keepPlaying = true;

    while (keepPlaying && game.getBankroll() > 0.0)
    {
        cout << endl;
        cout << "Current bankroll: $" << game.getBankroll() << endl;
        cout << "Cards remaining in shoe: " << game.getCardsRemaining() << endl;

        double betAmount = promptBetAmount(game);

        if (!game.startNewRound(betAmount))
        {
            cout << "Could not start round. Please try again." << endl;
            continue;
        }

        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << "Round " << game.getRoundNumber() << endl;
        cout << "----------------------------------------" << endl;

        cout << "Current Bet: $" << game.getCurrentBet() << endl;
        cout << "Bankroll after bet deduction: $" << game.getBankroll() << endl;

        if (game.wasShoeReshuffledBeforeCurrentRound())
        {
            cout << "The shoe was reshuffled before this round." << endl;
        }

        if (game.isLastHandBeforeShuffle())
        {
            cout << "This is the last hand before the shoe is shuffled." << endl;
        }

        while (!game.isRoundOver())
        {
            showTableState(game);

            string action = promptPlayerAction(game);

            if (action == "H")
            {
                game.playerHit();
            }
            else if (action == "S")
            {
                game.playerStand();
            }
            else if (action == "D")
            {
                game.playerDoubleDown();
            }
        }

        cout << endl;
        cout << "========== ROUND RESULT ==========" << endl;
        showTableState(game);
        cout << game.getRoundResultText() << endl;
        cout << "Payout returned: $" << game.getPayoutAmount() << endl;
        cout << "Updated bankroll: $" << game.getBankroll() << endl;

        writeRoundLogToFile(game);

        if (game.isReshufflePending())
        {
            cout << endl;
            cout << "The shoe will be reshuffled before the next round." << endl;
        }

        if (game.getBankroll() <= 0.0)
        {
            cout << endl;
            cout << "You are out of money. Session over." << endl;
            break;
        }

        keepPlaying = promptPlayAgain();
    }

    cout << endl;
    cout << "Thanks for playing Blackjack." << endl;
    return 0;
}

double promptStartingBankroll()
{
    double bankroll;

    while (true)
    {
        cout << "Enter starting bankroll: $";
        cin >> bankroll;

        if (cin.fail() || bankroll <= 0.0)
        {
            cout << "Please enter a valid amount greater than 0." << endl;
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

double promptBetAmount(const BlackjackGame& game)
{
    double betAmount;

    while (true)
    {
        cout << "Enter your bet: $";
        cin >> betAmount;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter a numeric bet." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (betAmount <= 0.0)
        {
            cout << "Bet must be greater than 0." << endl;
        }
        else if (betAmount > game.getBankroll())
        {
            cout << "You cannot bet more than your current bankroll." << endl;
        }
        else
        {
            return betAmount;
        }
    }
}

string promptPlayerAction(const BlackjackGame& game)
{
    string input;

    while (true)
    {
        cout << endl;
        cout << "Choose action: ";

        if (game.canHit())
        {
            cout << "[H]it ";
        }

        if (game.canStand())
        {
            cout << "[S]tand ";
        }

        if (game.canDoubleDown())
        {
            cout << "[D]ouble Down ";
        }

        cout << ": ";
        getline(cin, input);

        if (input.size() == 1)
        {
            char choice = toupper(input[0]);

            if (choice == 'H' && game.canHit())
            {
                return "H";
            }

            if (choice == 'S' && game.canStand())
            {
                return "S";
            }

            if (choice == 'D')
            {
                if (game.canDoubleDown())
                {
                    return "D";
                }
                else
                {
                    cout << "Double down is not available right now." << endl;
                    cout << "You need exactly 2 cards, it must be your first action, and you must have enough bankroll to match the current bet." << endl;
                    continue;
                }
            }
        }

        cout << "Invalid action. Please choose one of the available options." << endl;
    }
}

void showTableState(const BlackjackGame& game)
{
    cout << endl;
    cout << "Dealer Hand: ";

    if (game.isDealerHoleCardRevealed())
    {
        cout << game.getDealerHand().toString();
        cout << " (Value: " << game.getDealerValue() << ")" << endl;
    }
    else
    {
        cout << getDealerVisibleHand(game) << endl;
    }

    cout << "Player Hand: " << game.getPlayerHand().toString()
         << " (Value: " << game.getPlayerValue() << ")" << endl;
}

string getDealerVisibleHand(const BlackjackGame& game)
{
    vector<Card> dealerCards = game.getDealerHand().getCards();

    if (dealerCards.empty())
    {
        return "";
    }

    if (dealerCards.size() == 1)
    {
        return dealerCards[0].toString();
    }

    return dealerCards[0].toString() + " ??";
}

void showRoundLog(const BlackjackGame& game)
{
    vector<string> roundLog = game.getRoundLog();

    cout << "========== ROUND LOG ==========" << endl;

    for (const string& entry : roundLog)
    {
        cout << entry << endl;
    }
}

bool promptPlayAgain()
{
    string input;

    while (true)
    {
        cout << endl;
        cout << "Play another round? (Y/N): ";
        getline(cin, input);

        if (input.size() == 1)
        {
            char choice = toupper(input[0]);

            if (choice == 'Y')
            {
                return true;
            }

            if (choice == 'N')
            {
                return false;
            }
        }

        cout << "Please enter Y or N." << endl;
    }
}