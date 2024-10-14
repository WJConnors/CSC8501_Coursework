#include <iostream>
#include "ExperimentController.h"
using namespace std;

void ExperimentController::gameLoop()
{
	bool experiment{ true };
	while (experiment) {
		board = new Board();
		experimentCounter++;

		while (true){
			board->updateBoard();

			if (board->get_foundBlock() || board->get_foundBeehive()) {
				experiment = false;
				cout << "A static pattern has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundBlinker()) {
				experiment = false;
				cout << "An oscillator has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_ended()) {
				break;
			}
		}

		if (experiment) {
			delete(board);
		}
	}
	
	
	displayBoard();

}