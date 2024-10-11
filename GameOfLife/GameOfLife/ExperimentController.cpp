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
	
	cout << "A pattern has been found during experiment " << experimentCounter << endl;
	displayBoard();

}