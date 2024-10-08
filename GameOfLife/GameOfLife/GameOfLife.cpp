#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board board = Board();
	board.displayBoard();
	bool sim = true;
	while (sim) {
		cout << "Choose an option:" << endl;
		cout << "1. Step forward" << endl;
		cout << "2. End simulation" << endl;
		int in;
		cin >> in;

		switch (in) {
		case 1:
			board.updateBoard();
			board.displayBoard();
			break;
		case 2:
			sim = false;
		}
	}
}