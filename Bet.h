#pragma once

enum class BetType {
    NUMBER,
    RED,
    BLACK,
    EVEN,
    ODD,
    LOW,
    HIGH
};

struct Bet {
    BetType type;
    int value;
    int amount;
};
