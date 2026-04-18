#include "RouletteGame.h"
#include <cstdlib>

int RouletteGame::spin() {
    winningNumber = rand() % 37;
    return winningNumber;
}

bool RouletteGame::isRed(int number) {
    int reds[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    for (int r : reds) if (r == number) return true;
    return false;
}

int RouletteGame::evaluate(const BetManager& betManager) {
    int payout = 0;

    for (const Bet& bet : betManager.getBets()) {
        switch (bet.type) {
            case BetType::NUMBER:
                if (bet.value == winningNumber)
                    payout += bet.amount * 35;
                break;
            case BetType::RED:
                if (winningNumber != 0 && isRed(winningNumber))
                    payout += bet.amount * 2;
                break;
            case BetType::BLACK:
                if (winningNumber != 0 && !isRed(winningNumber))
                    payout += bet.amount * 2;
                break;
            case BetType::EVEN:
                if (winningNumber != 0 && winningNumber % 2 == 0)
                    payout += bet.amount * 2;
                break;
            case BetType::ODD:
                if (winningNumber % 2 == 1)
                    payout += bet.amount * 2;
                break;
            case BetType::LOW:
                if (winningNumber >= 1 && winningNumber <= 18)
                    payout += bet.amount * 2;
                break;
            case BetType::HIGH:
                if (winningNumber >= 19 && winningNumber <= 36)
                    payout += bet.amount * 2;
                break;
        }
    }

    return payout;
}
