#pragma once
#include "BetManager.h"

enum class GamePhase {
    BETTING,
    SPINNING,
    RESULT,
    WAITING_NEXT
};

class RouletteState {
public:
    int balance = 1000;
    int currentChip = 5;
    int lastResult = -1;

    float bettingTimer = 10.0f;
    GamePhase phase = GamePhase::BETTING;

    BetManager betManager;
};
