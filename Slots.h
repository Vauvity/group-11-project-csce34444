#ifndef SLOTS_H
#define SLOTS_H

#include <string>

class Slots {
private:
	//Symbols: B = bar, V = seven
	//		low-paying: J = jack, K = king, Q = queen, T = ten, 
	//		high-paying (themed): S = star, A = alien, M = moon, R = rocket
	char reel1[30] = {'B', 'J', 'S', 'T', 'J', 'K', 'A', 'M', 'M', 'V', 
						'R', 'B', 'S', 'Q', 'K', 'T', 'A', 'J', 'S', 'Q',
						'M', 'K', 'T', 'R', 'V', 'J', 'T', 'R', 'S', 'A'};
	char reel2[30] = {'J', 'K', 'A', 'T', 'Q', 'V', 'B', 'S', 'K', 'T',
						'B', 'A', 'M', 'Q', 'K', 'R', 'R', 'S', 'T', 'B',
						'M', 'S', 'V', 'A', 'B', 'T', 'J', 'Q', 'K', 'R'};
	char reel3[30] = {'T', 'B', 'Q', 'R', 'B', 'J', 'M', 'A', 'B', 'K',
						'J', 'Q', 'S', 'V', 'B', 'M', 'T', 'K', 'R', 'J',
						'B', 'S', 'A', 'M', 'Q', 'Q', 'K', 'J', 'V', 'T'};

	double bankroll;
	double initbank;
	double currentbet;
	double payout;
	bool won;

	int r1pos;
	int r2pos;
	int r3pos;

public:
	void reelsSpin();
	char getReel1Sym(int i);
	char getReel2Sym(int i);
	char getReel3Sym(int i);

	double paytable();

	void assignBank(double bank);
	void placeBet(double bet);

	bool checkBet();

	double getbankroll();

};


#endif