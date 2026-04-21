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
//			display, and stats.
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
							'Q', 'J', 'A', 'J', 'B'}, //reel 1

							{'R', 'J', 'A', 'J', 'Q', '7', 'B', 'S', 'J', 'Q',
							'B', 'A', 'R', 'Q', 'J', 'R', 'G', 'S', 'Q', 'B',
							'J', 'S', '7', 'A', 'B', 'R', 'J', 'Q', '5', 'R',
							'Q', 'A', '2', 'R', 'S'} , //reel 2

							{'J', 'B', 'Q', 'R', 'B', 'J', 'S', 'G', 'A', 'B', 
							'S', 'J', 'Q', '2', '7', 'B', 'R', 'Q', 'S', 'J', 
							'R', 'J', 'B', 'S', 'A', 'J', 'Q', 'Q', 'A', 'J', 
							'7', 'R', 'M', 'Q', 'J'}  //reel 3, the only one with mini jackpots
						};

//	SlotState gamestate;	//Stores current game state, NOT IN USE

	//BET, BANK, AND GAME VARIABLES
	double bankroll;			//Stores bankroll for stats purposes
	double initbank;			//What the bank originally was at the beginning of the session(?)
	double currentbet;			//Stores user bet amount
	void placeBet(double bet);	//function that intializes the user bet, called by reelsSpin
	double payout;				//Stores payout
	bool won;					//true if win, false if no win
	int spinNum = 0;			//Number of spin we're on in this session

	//SLOT SPIN VARIABLES
	int rpos[3];			//stores middle row positions for each reel
	SlotWindow slotw;		//A 3x3 slot machine window holding the symbols of the reels

	//PAYTABLE VARIABLES
	int highwins;				// Stores how many 3-in-a-row high symbols there were
	int lowwins;				// Stores how many 3-in-a-row low symbols there were
	int barseven;				// Stores how many 3-in-a-row Bars and Sevens there were
	int mult2;					// Stores how many 2x multipliers were encountered
	int mult5;					// Stores how many 5x multipliers were encountered
	double jackpotratio;		// Stores ratio to calculate mini or mega jackpot win

	//PROGRESSIVE JACKPOT VARIABLES AND FUNCTIONS
	double progjackpot = 20000.00;		// Stores the progressive jackpot
	double startjackpot = 20000.00;		// Stores the beginning prog jackpot for stats
	double amounttojackpot = 0.00;		// Stores the player bet amount put into the jackpot
	void updateProgJackpot(double bet);		// Updates the prog jackpot with player bet portion
	double winProgJackpot(double portion);	// Deals mini or mega jackpot win amount
	double jackpotPortion = 0.00;		// Stores portion of jackpot won

public:

	Slots(double startingBankroll);		// Initializes slot starting bankroll for stats
	SlotWindow reelsSpin(double b);		// Spins and "starts game." Takes bet, returns Slotwindow
	double paytable();					// Calculates paytable and returns payout
	SlotsSummary statSummary();			// Returns a struct with stats for each spin
	double displayProgressiveJackpot();	// Displays the progressive jackpot
};

#endif