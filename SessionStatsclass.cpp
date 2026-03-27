#include <fstream>

class SessionStats {
private:
    int totalSpins;
    int wins;
    int losses;

public:
    SessionStats() {
        totalSpins = 0;
        wins = 0;
        losses = 0;
    }

    void recordWin() {
        wins++;
        totalSpins++;
    }

    void recordLoss() {
        losses++;
        totalSpins++;
    }

    void displayStats(int balance) {
        cout << "\n=== SESSION STATS ===\n";
        cout << "Total Spins: " << totalSpins << "\n";
        cout << "Wins: " << wins << "\n";
        cout << "Losses: " << losses << "\n";

        if (totalSpins > 0) {
            cout << "Win Rate: " << (wins * 100.0 / totalSpins) << "%\n";
        }

        cout << "Final Balance: " << balance << "\n";
    }

    void saveToFile(int balance) {
        ofstream file("session_stats.txt", ios::app);

        file << "=== SESSION ===\n";
        file << "Spins: " << totalSpins << "\n";
        file << "Wins: " << wins << "\n";
        file << "Losses: " << losses << "\n";

        if (totalSpins > 0) {
            file << "Win Rate: " << (wins * 100.0 / totalSpins) << "%\n";
        }

        file << "Final Balance: " << balance << "\n";
        file << "------------------------\n";

        file.close();
    }
};
