#pragma once
#include <string>
#include "RouletteState.h"

class HintSystem {
public:
    std::string getHint(const RouletteState& state);
};

#include "HintSystem.h"

std::string HintSystem::getHint(const RouletteState& state){
    if(state.lastResult==-1) return "Place bets!";
    return (state.lastResult%2==0) ? "Try ODD" : "Try EVEN";
}
