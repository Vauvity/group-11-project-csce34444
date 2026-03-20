#include <iostream>
#include <string>
#include "Slots.h"

using namespace std;

int main() {
	double money;
	Slots slots;
	char cont;

	cout << "Welcome to Slots. Please tell us how much money is in your bank account:   $";
	cin >> money;
	slots.assignBank(money);
	do {
		cout << "Great! Now how much would you like to bet today?   $";
		cin >> money;
		slots.placeBet(money);
		if (!slots.checkBet()) {
			cout << "Sorry, you don't have enough money!" << endl;
		}
		else {
			cout << endl << "Alright, time to spin the wheel." << endl;
			slots.reelsSpin();
			cout << "Results: \n" << slots.getReel1Sym(1) << "   " << slots.getReel2Sym(1) << "   "
				<< slots.getReel3Sym(1) << endl;
			cout << slots.getReel1Sym(0) << "   " << slots.getReel2Sym(0) << "   " << slots.getReel3Sym(0) << endl;
			cout << slots.getReel1Sym(-1) << "   " << slots.getReel2Sym(-1) << "   " << slots.getReel3Sym(-1) << endl;
			cout << "Your payout is: " << slots.paytable() << endl;
			cout << "Your new bank balance is: " << slots.getbankroll();
		}
		cout << endl << "Would you like to play again? Y/N:   ";
		cin >> cont;
	} while (cont == 'Y' || cont == 'y');

	cout << "Thanks for playing!" << endl;
	return 0;
}