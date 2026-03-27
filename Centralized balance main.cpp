#include <iostream>
#include <string>
#include <limits>
 
//  Bankroll — single source of truth
class Bankroll {
private:
    int balance;
    int startingBalance;
    int peakBalance;
    int lowestBalance;

public:
    Bankroll(int startingAmount)
        : balance(startingAmount),
          startingBalance(startingAmount),
          peakBalance(startingAmount),
          lowestBalance(startingAmount) {}

    // Called by a game before a round (player places bet)
    bool withdraw(int amount) {
        if (amount <= 0 || amount > balance) {
            std::cout << "Invalid withdrawal amount.\n";
            return false;
        }
        balance -= amount;
        lowestBalance = std::min(lowestBalance, balance);
        return true;
    }

    // Called by a game after a round (payout)
    void deposit(int amount) {
        if (amount <= 0) return;
        balance += amount;
        peakBalance = std::max(peakBalance, balance);
    }

    // Getters
    int getBalance()        const { return balance; }
    int getStartingBalance()const { return startingBalance; }
    int getNetGainLoss()    const { return balance - startingBalance; }
    int getPeakBalance()    const { return peakBalance; }
    int getLowestBalance()  const { return lowestBalance; }
    bool isBroke()          const { return balance <= 0; }

    void printSummary() const {
        std::cout << "\n========== Bankroll Summary ==========\n";
        std::cout << "  Starting Balance : $" << startingBalance  << "\n";
        std::cout << "  Current Balance  : $" << balance          << "\n";
        std::cout << "  Peak Balance     : $" << peakBalance      << "\n";
        std::cout << "  Lowest Balance   : $" << lowestBalance    << "\n";
        std::cout << "  Net Gain/Loss    : $" << getNetGainLoss() << "\n";
        std::cout << "======================================\n";
    }
};

//  Game stubs — replace with real classes
//  Each game receives a Bankroll reference

void playBlackjack(Bankroll& bankroll) {
    std::cout << "\n[Blackjack] Current balance: $" << bankroll.getBalance() << "\n";
    // TODO: BlackjackGame game(bankroll); game.run();
    std::cout << "[Blackjack] (stub — plug your BlackjackGame class here)\n";
}

void playSlots(Bankroll& bankroll) {
    std::cout << "\n[Slots] Current balance: $" << bankroll.getBalance() << "\n";
    // TODO: SlotsGame game(bankroll); game.run();
    std::cout << "[Slots] (stub — plug your SlotsGame class here)\n";
}

void playRoulette(Bankroll& bankroll) {
    std::cout << "\n[Roulette] Current balance: $" << bankroll.getBalance() << "\n";
    // TODO: RouletteGame game(bankroll); game.run();
    std::cout << "[Roulette] (stub — plug your RouletteGame class here)\n";
}


//  Helpers
int getValidInt(const std::string& prompt, int minVal = 1) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal) break;
        std::cout << "Please enter a valid number (>= " << minVal << ").\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

void showMenu(const Bankroll& bankroll) {
    std::cout << "\n========== Casino Menu ==========\n";
    std::cout << "  Balance: $" << bankroll.getBalance() << "\n";
    std::cout << "---------------------------------\n";
    std::cout << "  1. Blackjack\n";
    std::cout << "  2. Slots\n";
    std::cout << "  3. Roulette\n";
    std::cout << "  4. View Bankroll Summary\n";
    std::cout << "  5. Cash Out & Exit\n";
    std::cout << "=================================\n";
    std::cout << "Choice: ";
}

//  Main
int main() {
    std::cout << "==============================\n";
    std::cout << "   Welcome to the Casino!\n";
    std::cout << "==============================\n";

    // One-time bankroll setup at program start
    int startingAmount = getValidInt("Enter your starting bankroll: $", 1);
    Bankroll bankroll(startingAmount);

    std::cout << "\nGood luck! Starting with $" << bankroll.getBalance() << "\n";

    int choice = 0;
    while (!bankroll.isBroke()) {
        showMenu(bankroll);

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: playBlackjack(bankroll); break;
            case 2: playSlots(bankroll);     break;
            case 3: playRoulette(bankroll);  break;
            case 4: bankroll.printSummary(); break;
            case 5:
                std::cout << "\nCashing out...\n";
                goto exitLoop;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }

    if (bankroll.isBroke()) {
        std::cout << "\nYou've run out of money! Game over.\n";
    }

exitLoop:
    bankroll.printSummary();
    std::cout << "\nThanks for playing!\n";
    return 0;
}
