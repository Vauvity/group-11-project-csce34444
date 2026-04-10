///*
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotsGame.cpp version 5
//		The SlotsGame class Slots
//	last updated: 4/9/26
//		UPDATE ADD: added paytable calculation values to stats summary.
//		UPDATE FIX: paytable now calculates payout correctly!
//*/

#include "SlotsGame.h"
#include <cstdlib>
#include <ctime>
#include "SlotWindow.h"
#include <stack>


//	CURRENT TO-DOS: (4/9/26)
//	-> Look into progressive jackpot/payout? (do some research)
//	-> Continue with error handling
//


//===========SLOTS FUNCTION==============
// Initializes the starting bankroll in 
// slots game and starting gamestate
Slots::Slots(double startingBankroll) {
	initbank = startingBankroll;
	bankroll = startingBankroll;
	highwins = 0;
	lowwins = 0;
	barseven = 0;
	mult2 = 0;
	mult5 = false;
//	gamestate = SlotState::WaitingForBet;
}// End Slots()


//===========PLACEBET FUNCTION==============
// Initializes the user bet. Called by reelsSpin
void Slots::placeBet(double bet) {
	currentbet = bet;
	bankroll -= bet;
//	gamestate = SlotState::Spinning;
} // End placeBet()


//===========REELSSPIN FUNCTION==============
// Spins the slot machine and returns class
// SlotWindow with the symbols shown in the
// slot machine window.
SlotWindow Slots::reelsSpin(double b) {
	placeBet(b);
	spinNum++;

	//RNG for all 3 reel posit holders seeded with the time
	srand(time(NULL));
	rpos[0] = rand() % 30;
	rpos[1] = rand() % 30;
	rpos[2] = rand() % 30;

	//Put reel symbols in an array
	for (int i = 0; i < 3; i++) {			//iterates through reels
		//middle posit on reel
		slotw.setDisplay(reels[i][rpos[i]], i, 1);
		//upper posit on reel
		if (rpos[i] == 0) {	//checks for top end of reel to put on bottom
			slotw.setDisplay(reels[i][29], i, 0);
		}
		else {
			slotw.setDisplay(reels[i][rpos[i] - 1], i, 0);
		}
		//lower posit on reel
		if (rpos[i] == 29) {	//checks for bottom end of reel to put on top
			slotw.setDisplay(reels[i][0], i, 2);
		}
		else {
			slotw.setDisplay(reels[i][rpos[i] + 1], i, 2);
		}
	}
	return slotw;
} // End reelsSpin()


//===========PAYTABLE FUNCTION==============
// Scans the reels and calculates the payout 
// of the spin. Returns payout.
double Slots::paytable() {
	payout = 0.0;
	won = false;
	highwins = 0;
	lowwins = 0;
	barseven = 0;
	mult2 = 0;
	mult5 = false;

	//check for multipliers
	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			if (slotw.getDisplay(r,c) == 'W') {
				mult2++;
				won = true;
			}
			else if (slotw.getDisplay(r, c) == 'F') {
				mult5 = true;	// currently only 1 5x multiplier can be disp @ a time
				won = true;
			}
		}
	}
	//check three in a row on rows
	for (int i = 0; i < 3; i++) {
		if (slotw.getDisplay(i, 0) == slotw.getDisplay(i, 1) && slotw.getDisplay(i, 0) 
					== slotw.getDisplay(i, 2)) 
		{
			char row3in = slotw.getDisplay(i, 0);
			if (row3in == 'J' || row3in == 'Q' || row3in == 'T' || row3in == 'K') {
				lowwins++;
			}
			else if (row3in == 'V' || row3in == 'B') {
				barseven++;
			}
			else {
				highwins++;
			}
			won = true;
		}
	}
	// Calculates the payout if there was a win
	if (won) {
		payout += currentbet;
		payout += lowwins * 50.00;
		payout += highwins * 200.00;
		payout += barseven * 750.00;
		if (mult2 > 0) {
			payout *= mult2 * 2;
		}
		if (mult5) {
			payout *= 5;
		}
	}
	bankroll += payout;	
	return payout;
} // End paytable()


//===========STATSUMMARY FUNCTION==============
// Creates and returns a struct SlotsSummary 
// that includes all of the stats from the
// current spin.
// **NOTE: the calculation of the paytable is still WIP bc of known errors**
SlotsSummary Slots::statSummary() {
	SlotsSummary roundStats;
	roundStats.spinNumber = spinNum;
	roundStats.startingBankroll = initbank;
	roundStats.betMade = currentbet;
	roundStats.payoutAmount = payout;
	roundStats.endingBankroll = bankroll;
	roundStats.netChange = bankroll - initbank;
	roundStats.slotDisplay = slotw;
	
	//Pay calculations listed below:
	roundStats.numLowWins = lowwins;	//adds $50
	roundStats.numHighWins = highwins;	//adds $200
	roundStats.numBarOr7 = barseven;	//adds $750
	roundStats.num2Multiply = mult2;	//multiplies total payout by 2x
	if (mult5) {						//multiplies total payout by 5x
		roundStats.num5Multiply = 1;
	}

	return roundStats;
} // End statSummary()


//space saver for displaying how payout calculated