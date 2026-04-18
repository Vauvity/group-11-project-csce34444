#pragma once
#include "BetManager.h"

class RouletteGame {
private:
    int winningNumber;

public:
    int spin();
    int evaluate(const BetManager& betManager);

private:
    bool isRed(int number);
};
