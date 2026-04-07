///*
//	Elizabeth Stillwell
//	CSCE-3444-400, Software Engineering
//	University of North Texas
//	Professor Bahareh M. Dorri
//
//	Team Galactic's Space Casino casino simulator project
//	Slots Module
//	SlotTypes.h version 4
//		SlotTypes creates slot game states and the groundworks for the slot stats
//	last updated: 4/6/26
//		UPDATE ADD: adds groundwork for payout calculation variables. WIP
//*/

#ifndef SLOTTYPES_H
#define SLOTTYPES_H

#include <stack>
#include "SlotWindow.h"

// CURRENTLY OUT OF COMMISSION - did not need but can implement
//enum class SlotState {		//Game states. WIP and currently not in use
//	WaitingForBet,
//	Bust,
//	Spinning
//};

struct SlotsSummary {		//The skeleton of slots stats for backend and session stats
	int spinNumber = 0;						// Number of spin in this session
	double startingBankroll = 0.0;
	double betMade = 0.0;
	double payoutAmount = 0.0;
	double endingBankroll = 0.0;
	double netChange = 0.0;

	// int reelPosit[3];		// Maybe come back to this later? for displaying what part of reel selected
										//	on the entire reel
	SlotWindow slotDisplay;		// Holds the display of the window

	//std::stack<char> paytablCalc;		//Stack to store the payout calculation method
			//char paytablCalc[7];		// Holds payCalc stack list
	// NOTE TO PRAYUSH: Above are two possible ways I will be passing the payout calculation.
	// Still troubleshooting

};


#endif