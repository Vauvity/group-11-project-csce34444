#include "Slots.h"
#include <cstdlib>

using namespace std;

//Slots::Slots() {
//
//}

void Slots::placeBet(double bet) {
	currentbet = bet;
	bankroll -= bet;
}

void Slots::assignBank(double bank) {
	initbank = bank;
	bankroll = bank;
}

bool Slots::checkBet() {
	if (currentbet > bankroll)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Slots::reelsSpin() {
	//RNG for all 3 reel posit holders
	r1pos = std::rand() % 30;
	r2pos = std::rand() % 30;
	r3pos = std::rand() % 30;
}

// i ranges from 0 (middle), 1 (top), and -1 (bottom) for vals disp
char Slots::getReel1Sym(int i) {	
	return reel1[r1pos + i];
}
char Slots::getReel2Sym(int i) {
	return reel2[r2pos + i];
}
char Slots::getReel3Sym(int i) {
	return reel3[r3pos + i];
}

double Slots::getbankroll() {
	return bankroll;
}

double Slots::paytable() {
	payout = 0;
	won = 0;

	//check three in a row on rows
	//TOP ROW
	if (reel1[r1pos + 1] == reel2[r2pos + 1] && reel1[r1pos + 1] == reel3[r3pos + 1]) {
		if (reel1[r1pos + 1] == 'J' || reel1[r1pos + 1] == 'Q' || reel1[r1pos + 1] == 'T' ||
						reel1[r1pos + 1] == 'K') {
			payout += 50;
		}
		else if (reel1[r1pos + 1] == 'V' || reel1[r1pos + 1] == 'B') {
			payout += 750;
		}
		else {
			payout += 200;
		}
		won = 1;
	}
	//MIDDLE ROW
	if (reel1[r1pos] == reel2[r2pos] && reel1[r1pos] == reel3[r3pos]) {
		if (reel1[r1pos] == 'J' || reel1[r1pos] == 'Q' || reel1[r1pos] == 'T' ||
			reel1[r1pos] == 'K') {
			payout += 50;
		}
		else if (reel1[r1pos] == 'V' || reel1[r1pos] == 'B') {
			payout += 750;
		}
		else {
			payout += 200;
		}
		won = 1;
	}
	//BOTTOM ROW
	if (reel1[r1pos - 1] == reel2[r2pos - 1] && reel1[r1pos - 1] == reel3[r3pos - 1]) {
		if (reel1[r1pos - 1] == 'J' || reel1[r1pos - 1] == 'Q' || reel1[r1pos - 1] == 'T' ||
			reel1[r1pos - 1] == 'K') {
			payout += 50;
		}
		else if (reel1[r1pos - 1] == 'V' || reel1[r1pos - 1] == 'B') {
			payout += 750;
		}
		else {
			payout += 200;
		}
		won = 1;
	}

	if (won) {
		payout += currentbet;
	}
	bankroll += payout;
	return payout;
}