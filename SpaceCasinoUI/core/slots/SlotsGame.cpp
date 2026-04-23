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

Slots::Slots(double startingBankroll) {
	initbank = startingBankroll;
	bankroll = startingBankroll;
	highwins = 0;
	lowwins = 0;
	barseven = 0;
	mult2 = 0;
	mult5 = 0;
	jackpotratio = 0.0;
	payout = 0.0;
	won = false;
	currentbet = 0.0;
	seededRng = false;
}

void Slots::ensureSeeded() {
	if (!seededRng) {
		srand(static_cast<unsigned int>(time(NULL)));
		seededRng = true;
	}
}

void Slots::placeBet(double bet) {
	currentbet = bet;
	updateProgJackpot(currentbet);
	bankroll -= bet;
}

SlotWindow Slots::reelsSpin(double b) {
	placeBet(b);
	spinNum++;
	ensureSeeded();

	rpos[0] = rand() % 35;
	rpos[1] = rand() % 35;
	rpos[2] = rand() % 35;

	for (int i = 0; i < 3; i++) {
		slotw.setDisplay(reels[i][rpos[i]], i, 1);
		if (rpos[i] == 0) {
			slotw.setDisplay(reels[i][34], i, 0);
		}
		else {
			slotw.setDisplay(reels[i][rpos[i] - 1], i, 0);
		}
		if (rpos[i] == 34) {
			slotw.setDisplay(reels[i][0], i, 2);
		}
		else {
			slotw.setDisplay(reels[i][rpos[i] + 1], i, 2);
		}
	}
	return slotw;
}

double Slots::paytable() {
	payout = 0.0;
	won = false;
	highwins = 0;
	lowwins = 0;
	barseven = 0;
	mult2 = 0;
	mult5 = 0;
	jackpotratio = 0.0;

	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			if (slotw.getDisplay(r, c) == '2') {
				mult2++;
				won = true;
			}
			else if (slotw.getDisplay(r, c) == '5') {
				mult5++;
				won = true;
			}
		}
	}

	for (int d = 0; d < 3; d++) {
		if (slotw.getDisplay(d, 2) == 'M') {
			jackpotratio = 120.0;
			won = true;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (slotw.getDisplay(i, 0) == slotw.getDisplay(i, 1) &&
			slotw.getDisplay(i, 0) == slotw.getDisplay(i, 2))
		{
			char row3in = slotw.getDisplay(i, 0);
			if (row3in == 'J' || row3in == 'Q') {
				lowwins++;
			}
			else if (row3in == '7' || row3in == 'B') {
				barseven++;
			}
			else if (row3in == 'G') {
				jackpotratio = 1.0;
			}
			else {
				highwins++;
			}
			won = true;
		}
	}

	if (won) {
		payout += currentbet;
		payout += lowwins * 100.00;
		payout += highwins * 500.00;
		payout += barseven * 1000.00;
		if (mult2 > 0) {
			payout *= mult2 * 2;
		}
		if (mult5 > 0) {
			payout *= mult5 * 5;
		}
		if (jackpotratio > 0.0) {
			payout += winProgJackpot(jackpotratio);
		}
	}

	bankroll += payout;
	return payout;
}

SlotsSummary Slots::statSummary() {
	SlotsSummary roundStats;
	roundStats.spinNumber = spinNum;
	roundStats.startingBankroll = initbank;
	roundStats.betMade = currentbet;
	roundStats.payoutAmount = payout;
	roundStats.endingBankroll = bankroll;
	roundStats.netChange = bankroll - initbank;
	roundStats.slotDisplay = slotw;
	roundStats.numLowWins = lowwins;
	roundStats.numHighWins = highwins;
	roundStats.numBarOr7 = barseven;
	roundStats.num2Multiply = mult2;
	roundStats.num5Multiply = mult5;
	if (jackpotratio > 0.0) {
		roundStats.wonJackpot = 'Y';
		if (jackpotratio == 1.0) {
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
}

double Slots::displayProgressiveJackpot() {
	return progjackpot;
}

void Slots::updateProgJackpot(double bet) {
	if (progjackpot <= 0.00) {
		progjackpot = 20000.00;
	}
	amounttojackpot = bet / 10;
	startjackpot = progjackpot;
	progjackpot += amounttojackpot;
}

double Slots::winProgJackpot(double portion) {
	jackpotPortion = progjackpot / portion;
	progjackpot -= jackpotPortion;
	return jackpotPortion;
}

double Slots::getBankroll() const {
	return bankroll;
}
