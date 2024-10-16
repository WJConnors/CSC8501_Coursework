#include <iostream>
#include "ExperimentController.h"
using namespace std;

void ExperimentController::gameLoop()
{
	cout << "Input board x size, y size, and number of starting alive cells:" << endl;
	int x, y, a;
	cin >> x;
	cin >> y;
	cin >> a;
	bool experiment{ true };
	while (experiment) {
		board = new Board(x, y, a);
		experimentCounter++;

		while (true){

			if (board->get_foundBlock() || board->get_foundBeehive()) {
				experiment = false;
				cout << "A static pattern has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundBlinker() || board->get_foundToad()) {
				experiment = false;
				cout << "An oscillator has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundGlider() || board->foundLWSS) {
				experiment = false;
				cout << "A spaceship has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_ended() || board->foundLWSS) {
				break;
			}

			++ * board;
		}

		if (experiment) {
			delete(board);
		}
	}
	
	
	displayAllBoards();

}