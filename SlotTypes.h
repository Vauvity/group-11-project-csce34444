//
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotTypes.h version 6
//		SlotTypes creates slot game states and the groundworks for the slot stats
//	last updated: 4/20/26
//		UPDATE ADD: added progressive jackpot functions to stats
//

#ifndef SLOTTYPES_H
#define SLOTTYPES_H

#include <stack>
#include "SlotWindow.h"


struct SlotsSummary {		//The skeleton of slots stats for backend and session stats

	//GAME AND MONEY DETAILS
	int spinNumber = 0;						// Number of spin in this session
	double startingBankroll = 0.0;
	double betMade = 0.0;
	double payoutAmount = 0.0;
	double endingBankroll = 0.0;
	double netChange = 0.0;

	//SPIN DETAILS
	SlotWindow slotDisplay;		// Holds the display of the window

	//PAYTABLE CALCULATIONS
	int numLowWins = 0;
	int numHighWins = 0;
	int numBarOr7 = 0;
	int num2Multiply = 0;
	int num5Multiply = 0;
	char wonJackpot = 'N';		// N = no jackpot win, Y = yes jackpot win
	char typeJackpot = '0';		// 0 = no jackpot win, M = Mega jackpot, m = mini jackpot

	//PROGRESSIVE JACKPOT DETAILS
	double startingJackpot = 0.0;
	double endingJackpot = 0.0;
	double amountToJackpot = 0.0;
};


// CURRENTLY OUT OF COMMISSION - did not need but can implement
//enum class SlotState {		//Game states. WIP and currently not in use
//	WaitingForBet,
//	Bust,
//	Spinning
//};

#endif