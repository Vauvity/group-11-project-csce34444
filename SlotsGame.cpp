///*
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotsGame.cpp version 4
//		The SlotsGame class Slots
//	last updated: 4/6/26
//		UPDATE ADD: add the function SlotsSummary statSummary() to pass struct with
//		slot spin stats through.
//		UPDATE FIX: fixes issue with reading the reels in the correct order
//*/

#include "SlotsGame.h"
#include <cstdlib>
#include <ctime>
#include "SlotWindow.h"
#include <stack>


//	CURRENT TO-DOS: (4/6/26)
//	-> Keep troubleshooting to identify paytable calculation flaws
// 
//	-> Look into progressive jackpot/payout? (do some research)
//	-> Continue with error handling
//


//===========SLOTS FUNCTION==============
// Initializes the starting bankroll in 
// slots game and starting gamestate
Slots::Slots(double startingBankroll) {
	initbank = startingBankroll;
	bankroll = startingBankroll;
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
	payout = 0;
	won = 0;

	//CURRENT BUGS:
	// Not properly calculating payout because of stack handling (current conspiracy)
	// Unable to recognize multipliers showing up (?may be caused by above issue)

	//check for multipliers
	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			if (reels[r][c] == 'W') {
				payCalc.push('w');
				won = 1;
			}
			else if (reels[r][c] == 'F') {
				payCalc.push('f');
				won = 1;
			}
		}
	}
	//check three in a row on rows
	for (int i = 0; i < 3; i++) {
		if (reels[i][0] == reels[i][1] && reels[0][i] == reels[i][2]) {
			if (reels[i][0] == 'J' || reels[i][0] == 'Q' || reels[i][0] == 'T' ||
					reels[i][0] == 'K') {
				payCalc.push('l');
			}
			else if (reels[i][0] == 'V' || reels[i][0] == 'B') {
				payCalc.push('b');
			}
			else {
				payCalc.push('h');
			}
			won = 1;
		}
	}
	// Calculates the payout if there was a win
	if (won) {
		payout += currentbet;
		//insert loop for item in stack, assess payout
		while (!payCalc.empty()) {
			switch (payCalc.top()) {
			case 'h':	//high-paying
				payout += 200;
			case 'l':	//low-paying
				payout += 50;
			case 'b':
				payout += 750;
			case 'w':
				payout *= 2;
			case 'f':
				payout *= 5;
			}
			payCalc.pop();
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
	//roundStats.paytablCalc = ;		//pay table calculation still WIP

	return roundStats;
} // End statSummary()



//TESTING FUNCT ONLY!!!
char Slots::dispStack() {
	return payCalc.top();
}