#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board* board = new Board();
	board->displayBoard();
	bool sim = true;
	while (sim) {
		cout << "Choose an option:" << endl;
		cout << "1. Step forward" << endl;
		cout << "2. End simulation" << endl;
		cout << "3. Save current state" << endl;
		int in;
		cin >> in;

		switch (in) {
		case 1:
			board->updateBoard();
			board->displayBoard();
			break;
		case 2:
			sim = false;
			break;
		case 3:
			board->saveBoard("test.txt");
			break;
		}
	}
	board->displayOriginalBoard();

	delete(board);
}