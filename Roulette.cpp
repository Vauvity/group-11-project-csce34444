#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to get color
string getColor(int number) {
    if (number == 0) return "Green";
    if (number % 2 == 0) return "Black";
    return "Red";
}

int main() {
    srand(time(0));

    int balance, betAmount;
    const int TOTAL_SESSIONS = 10;

    // Starting balance
    cout << "Enter your starting balance: ";
    cin >> balance;
    while (balance <= 0) {
        cout << "Invalid. Enter > 0: ";
        cin >> balance;
    }

    // Initial bet
    cout << "Enter your bet amount: ";
    cin >> betAmount;
    while (betAmount <= 0 || betAmount > balance) {
        cout << "Invalid bet. Enter valid amount: ";
        cin >> betAmount;
    }

    // Stats
    int wins = 0, losses = 0, totalSpins = 0;

    cout << "\n=== SPACE CASINO ROULETTE ===\n";

    for (int session = 1; session <= TOTAL_SESSIONS; session++) {
        if (balance <= 0) break;

        cout << "\n--- Round " << session << " ---\n";
        cout << "Balance: " << balance << "\n";

        // MENU
        int option;
        cout << "\nOptions:\n";
        cout << "1. Play round\n";
        cout << "2. Change bet\n";
        cout << "3. Exit game\n";
        cout << "Choice: ";
        cin >> option;

        if (option == 3) {
            cout << "Exiting game early...\n";
            break;
        }

        if (option == 2) {
            cout << "Enter new bet amount: ";
            cin >> betAmount;
            while (betAmount <= 0 || betAmount > balance) {
                cout << "Invalid bet. Enter valid amount: ";
                cin >> betAmount;
            }
            cout << "Bet updated to: " << betAmount << "\n";
            session--;
            continue;
        }

        if (option != 1) {
            cout << "Invalid choice. Try again.\n";
            session--;
            continue;
        }

        // 🚫 ENFORCE BET RULE HERE
        while (betAmount > balance) {
            cout << "You don't have enough balance for this bet unfortunately.\n";
            cout << "Enter a new bet amount: ";
            cin >> betAmount;
        }

        // User chooses bet type
        int betType;
        cout << "Choose bet type:\n";
        cout << "1. Color\n2. Number\n3. Both\nChoice: ";
        cin >> betType;

        string chosenColor;
        int chosenNumber;

        if (betType == 1) {
            cout << "Enter color (Red/Black): ";
            cin >> chosenColor;
        }
        else if (betType == 2) {
            cout << "Enter number (0-36): ";
            cin >> chosenNumber;
        }
        else if (betType == 3) {
            cout << "Enter color (Red/Black): ";
            cin >> chosenColor;
            cout << "Enter number (0-36): ";
            cin >> chosenNumber;
        } else {
            cout << "Invalid choice. Skipping round.\n";
            continue;
        }

        // Spin wheel
        int spin = rand() % 37;
        string spinColor = getColor(spin);

        cout << "Spin Result: " << spin << " (" << spinColor << ")\n";

        bool win = false;

        // Evaluate bets
        if (betType == 1) {
            if (spinColor == chosenColor) {
                balance += betAmount;
                win = true;
            } else {
                balance -= betAmount;
            }
        }
        else if (betType == 2) {
            if (spin == chosenNumber) {
                balance += betAmount * 35;
                win = true;
            } else {
                balance -= betAmount;
            }
        }
        else if (betType == 3) {
            if (spin == chosenNumber && spinColor == chosenColor) {
                balance += betAmount * 40;
                win = true;
            } else {
                balance -= betAmount;
            }
        }

        // Stats update
        totalSpins++;
        if (win) {
            cout << "WIN!\n";
            wins++;
        } else {
            cout << "LOSS.\n";
            losses++;
        }

        cout << "New Balance: " << balance << "\n";
    }

    // Final stats
    cout << "\n=== Your FINAL STATS are ===\n";
    cout << "Total Spins: " << totalSpins << "\n";
    cout << "Total Wins: " << wins << "\n";
    cout << "Total Losses: " << losses << "\n";

    if (totalSpins > 0)
        cout << "Win Rate: " << (wins * 100.0 / totalSpins) << "%\n";

    cout << "Your final balance is: " << balance << "\n";

    return 0;
}
