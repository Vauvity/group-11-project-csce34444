#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

// -----------------------------
// INITIAL SETUP
// -----------------------------
const int STARTING_BALANCE = 1000;
int balance = STARTING_BALANCE;

vector<int> wheel;
set<int> red_numbers = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

// Stats
vector<int> spin_history;
int total_spins = 0;
int wins = 0;
int losses = 0;
int total_wagered = 0;

// -----------------------------
// CORE FUNCTIONS
// -----------------------------
int spin_wheel() {
    int result = wheel[rand() % wheel.size()];
    spin_history.push_back(result);
    total_spins++;
    return result;
}

string get_color(int number) {
    if (number == 0) return "green";
    return (red_numbers.count(number)) ? "red" : "black";
}

// -----------------------------
// HINT SYSTEM
// -----------------------------
void show_hint() {
    if (total_spins < 3) {
        cout << "\nHint unlocks after 3 spins.\n";
        return;
    }

    int red_count = 0, black_count = 0;

    int start = max(0, (int)spin_history.size() - 5);
    for (int i = start; i < spin_history.size(); i++) {
        string color = get_color(spin_history[i]);
        if (color == "red") red_count++;
        else if (color == "black") black_count++;
    }

    cout << "\nHINT SYSTEM:\n";

    if (red_count > black_count)
        cout << "Red trend detected -> Consider BLACK\n";
    else if (black_count > red_count)
        cout << "Black trend detected -> Consider RED\n";
    else
        cout << "Balanced -> Try NUMBER bet\n";
}

// -----------------------------
// BET STRUCT
// -----------------------------
struct Bet {
    string type;
    int amount;
    int number;
    string color;
};

// -----------------------------
// BETTING SYSTEM
// -----------------------------
bool place_bet(Bet &bet) {
    while (true) {
        cout << "\n=== BET MENU ===\n";
        cout << "1 - Number Bet\n";
        cout << "2 - Color Bet\n";
        cout << "3 - Number + Color Bet\n";
        cout << "4 - Hint\n";
        cout << "5 - Quit Game\n";

        string choice;
        cin >> choice;

        if (choice == "5") return false;

        if (choice == "4") {
            show_hint();
            continue;
        }

        if (choice == "1") {
            bet.type = "number";
            cout << "Enter bet amount: ";
            cin >> bet.amount;
            cout << "Choose number (0-36): ";
            cin >> bet.number;
            return true;
        }

        else if (choice == "2") {
            bet.type = "color";
            cout << "Enter bet amount: ";
            cin >> bet.amount;
            cout << "Choose color (red/black): ";
            cin >> bet.color;
            return true;
        }

        else if (choice == "3") {
            bet.type = "combo";
            cout << "Enter total bet amount: ";
            cin >> bet.amount;
            cout << "Choose number (0-36): ";
            cin >> bet.number;
            cout << "Choose color (red/black): ";
            cin >> bet.color;
            return true;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }
}

// -----------------------------
// WIN CALCULATION
// -----------------------------
int calculate_winnings(Bet bet, int result) {
    string color = get_color(result);

    if (bet.type == "number") {
        if (bet.number == result) {
            wins++;
            return bet.amount * 35;
        }
    }

    else if (bet.type == "color") {
        if (bet.color == color) {
            wins++;
            return bet.amount * 2;
        }
    }

    else if (bet.type == "combo") {
        int num_win = (bet.number == result) ? bet.amount * 25 : 0;
        int color_win = (bet.color == color) ? bet.amount * 1.5 : 0;

        if (num_win > 0 || color_win > 0) {
            wins++;
            return num_win + color_win;
        }
    }

    losses++;
    return 0;
}

// -----------------------------
// DISPLAY SUMMARY
// -----------------------------
void show_summary() {
    cout << "\nFINAL SUMMARY\n";
    cout << "Starting Balance: " << STARTING_BALANCE << endl;
    cout << "Final Balance: " << balance << endl;
    cout << "Total Spins: " << total_spins << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
    cout << "Total Wagered: " << total_wagered << endl;

    if (total_spins > 0) {
        double win_rate = (double)wins / total_spins * 100;
        cout << "Win Rate: " << win_rate << "%\n";
    }
}

// -----------------------------
// MAIN GAME LOOP
// -----------------------------
void play_game() {
    cout << "Welcome to Space Casino Roulette\n";

    while (balance > 0) {
        cout << "\nBalance: " << balance << endl;

        cout << "Recent Spins: ";
        for (int i = max(0, (int)spin_history.size() - 5); i < spin_history.size(); i++) {
            cout << spin_history[i] << " ";
        }
        cout << endl;

        Bet bet;
        if (!place_bet(bet)) {
            cout << "You chose to quit.\n";
            break;
        }

        if (bet.amount > balance) {
            cout << "Not enough balance!\n";
            continue;
        }

        balance -= bet.amount;
        total_wagered += bet.amount;

        cout << "\nSpinning...\n";
        int result = spin_wheel();
        string color = get_color(result);

        cout << "Result: " << result << " (" << color << ")\n";

        int winnings = calculate_winnings(bet, result);

        if (winnings > 0) {
            cout << "You won $" << winnings << endl;
            balance += winnings;
        } else {
            cout << "You lost\n";
        }
    }

    if (balance <= 0) {
        cout << "You lost all your money!\n";
    }

    show_summary();
}

// -----------------------------
// MAIN
// -----------------------------
int main() {
    srand(time(0));

    for (int i = 0; i <= 36; i++) {
        wheel.push_back(i);
    }

    play_game();
    return 0;
}
