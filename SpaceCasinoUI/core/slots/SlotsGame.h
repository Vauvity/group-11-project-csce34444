//
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotsGame.h version 6
//		Creates the SlotsGame class Slots
//	last updated: 4/20/26
//		UPDATE ADD: added progressive jackpot functions to game,
//		display, and stats.
//		UPDATE FIX: changed slots symbols to increase odds of winning
//

#ifndef SLOTSGAME_H
#define SLOTSGAME_H

#include <string>
#include "SlotWindow.h"
#include <stack>
#include "SlotTypes.h"

class Slots {
private:
	//THE SLOT REELS THEMSELVES
	//Symbols: B = bar, 7 = seven
	//		low-paying: J = jack, Q = queen,
	//		high-paying (themed): S = star, A = alien, R = rocket
	//		multipliers: 2 = 2x, 5 = 5x
	//		jackpot: G = galaxy (mega jackpot), M = moon (mini jackpot)
	char reels[3][35] = { {'B', 'J', 'S', 'Q', 'J', 'J', 'A', 'Q', 'S', 'G',
							'R', 'B', 'S', 'Q', 'J', 'Q', 'A', 'J', '7', 'Q',
							'R', 'J', 'S', 'R', '7', 'J', 'A', 'R', 'S', 'A',
							'Q', 'J', 'A', 'J', 'B'},

							{'R', 'J', 'A', 'J', 'Q', '7', 'B', 'S', 'J', 'Q',
							'B', 'A', 'R', 'Q', 'J', 'R', 'G', 'S', 'Q', 'B',
							'J', 'S', '7', 'A', 'B', 'R', 'J', 'Q', '5', 'R',
							'Q', 'A', '2', 'R', 'S'} ,

							{'J', 'B', 'Q', 'R', 'B', 'J', 'S', 'G', 'A', 'B',
							'S', 'J', 'Q', '2', '7', 'B', 'R', 'Q', 'S', 'J',
							'R', 'J', 'B', 'S', 'A', 'J', 'Q', 'Q', 'A', 'J',
							'7', 'R', 'M', 'Q', 'J'}
						};

	double bankroll;
	double initbank;
	double currentbet;
	void placeBet(double bet);
	double payout;
	bool won;
	int spinNum = 0;

	int rpos[3];
	SlotWindow slotw;

	int highwins;
	int lowwins;
	int barseven;
	int mult2;
	int mult5;
	double jackpotratio;

	double progjackpot = 20000.00;
	double startjackpot = 20000.00;
	double amounttojackpot = 0.00;
	void updateProgJackpot(double bet);
	double winProgJackpot(double portion);
	double jackpotPortion = 0.00;

	bool seededRng;
	void ensureSeeded();

public:
	Slots(double startingBankroll = 1000.0);
	SlotWindow reelsSpin(double b);
	double paytable();
	SlotsSummary statSummary();
	double displayProgressiveJackpot();
	double getBankroll() const;
};

#endif
