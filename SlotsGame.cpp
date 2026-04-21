//
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotsGame.cpp version 6
//		The SlotsGame class Slots
//	last updated: 4/20/26
//		UPDATE ADD: added progressive jackpot functions to game, 
//			display, and stats
//		UPDATE FIX: increased payout amounts for 3 in a row
//

#include "SlotsGame.h"
#include <cstdlib>
#include <ctime>
#include "SlotWindow.h"
#include <stack>


//	CURRENT TO-DOS: (4/20/26)
//	-> Calculate all odds
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
	jackpotratio = 0.0;
	//	gamestate = SlotState::WaitingForBet;
}// End Slots()


//===========PLACEBET FUNCTION==============
// Initializes the user bet. Called by reelsSpin
void Slots::placeBet(double bet) {
	currentbet = bet;
	updateProgJackpot(currentbet);
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
	rpos[0] = rand() % 31;
	rpos[1] = rand() % 31;
	rpos[2] = rand() % 31;

	//Put reel symbols in an array
	for (int i = 0; i < 3; i++) {			//iterates through reels
		//middle posit on reel
		slotw.setDisplay(reels[i][rpos[i]], i, 1);
		//upper posit on reel
		if (rpos[i] == 0) {	//checks for top end of reel to put on bottom
			slotw.setDisplay(reels[i][30], i, 0);
		}
		else {
			slotw.setDisplay(reels[i][rpos[i] - 1], i, 0);
		}
		//lower posit on reel
		if (rpos[i] == 30) {	//checks for bottom end of reel to put on top
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
	mult5 = 0;
	jackpotratio = 0.0;

	//check for multipliers
	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			if (slotw.getDisplay(r,c) == '2') {
				mult2++;
				won = true;
			}
			else if (slotw.getDisplay(r, c) == '5') {
				mult5++;	// currently only 1 5x multiplier can be disp @ a time
				won = true;
			}
		}
	}
	//check for jackpots
	for (int d = 0; d < 3; d++) {
		if (slotw.getDisplay(d, 2) == 'N') {	//Mini jackpot; 1/120 of jackpot
			jackpotratio = 120.0;
			won = true;
		}
	}
	//check three in a row on rows
	for (int i = 0; i < 3; i++) {
		if (slotw.getDisplay(i, 0) == slotw.getDisplay(i, 1) && slotw.getDisplay(i, 0) 
					== slotw.getDisplay(i, 2)) 
		{
			char row3in = slotw.getDisplay(i, 0);
			if (row3in == 'J' || row3in == 'Q') {
				lowwins++;
			}
			else if (row3in == '7' || row3in == 'B') {
				barseven++;
			}
			else if (row3in == 'G') {		//Mega jackpot = full prog jackpot
				jackpotratio = 1.0;
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
		payout += lowwins * 100.00;
		payout += highwins * 500.00;
		payout += barseven * 1000.00;
		if (mult2 > 0) {
			payout *= mult2 * 2;
		}
		if (mult5) {
			payout *= mult5 * 5;
		}
		if (jackpotratio > 0.0) {
			payout += winProgJackpot(jackpotratio);
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
	roundStats.numLowWins = lowwins;	//adds $100
	roundStats.numHighWins = highwins;	//adds $500
	roundStats.numBarOr7 = barseven;	//adds $1000
	roundStats.num2Multiply = mult2;	//multiplies total payout by 2x		
	roundStats.num5Multiply = mult5;	//multiplies total payout by 5x
	if (jackpotratio > 0.0) {			
		roundStats.wonJackpot = 'Y';	//tells if a jackpot was won and saves
		if (jackpotratio == 1.0) {		//  M for Mega and m for mini
			roundStats.typeJackpot = 'M';	
		}
		else {
			roundStats.typeJackpot = 'm';
		}
	}

	roundStats.startingJackpot = startjackpot;
	roundStats.endingJackpot = progjackpot;
	roundStats.amountToJackpot = amounttojackpot;

	return roundStats;
} // End statSummary()


//space saver for displaying how payout calculated


//=======DISPLAYPROGRESSIVEJACKPOT FUNCTION==========
// Returns the current progressive jackpot for display
// purposes. Should be called at the beginning of
// each spin to update the jackpot for every bet
double Slots::displayProgressiveJackpot() {
	return progjackpot;
} // End displayProgressiveJackpot()


//=======UPDATEPROGJACKPOT FUNCTION==========
// Updates the progressive jackpot and stores money
// put into the progressive jackpot for stats
void Slots::updateProgJackpot(double bet) {
	if (progjackpot <= 0.00) {		//resets to casino starter jackpot amount
		progjackpot = 20000.00;		//	of $20k if a mega win recently happened
	}
	amounttojackpot = bet / 10;
	startjackpot = progjackpot;
	progjackpot += amounttojackpot;
} // End updateProgJackpot


//=======WINPROGJACKPOT FUNCTION==========
// Updates the progressive jackpot upon win
// and deals mini or mega jackpot depending on
// jackpot ratio. Mini = 1/120, Mega = 1/1
double Slots::winProgJackpot(double portion) {
	jackpotPortion = progjackpot / portion;
	progjackpot -= jackpotPortion;
	return jackpotPortion;
} // End winProgJackpot