#pragma once
#include <vector>
#include "Bet.h"

class BetManager {
private:
    std::vector<Bet> bets;

public:
    void addBet(BetType type, int value, int amount);
    void clearBets();
    const std::vector<Bet>& getBets() const;
};
