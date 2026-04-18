#pragma once

class SessionStats {
public:
    int spins=0,wins=0,losses=0;

    void record(int payout){
        spins++;
        if(payout>0) wins++;
        else losses++;
    }
};

#include "SessionStats.h"
