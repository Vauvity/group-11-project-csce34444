#include "BetManager.h"

void BetManager::addBet(BetType type, int value, int amount) {
    bets.push_back({type, value, amount});
}

void BetManager::clearBets() {
    bets.clear();
}

const std::vector<Bet>& BetManager::getBets() const {
    return bets;
}
