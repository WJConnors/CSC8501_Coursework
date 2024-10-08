#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	cout << "Choose an option:" << endl;
	cout << "1. Create a new board" << endl;
	cout << "2. Load the saved board" << endl;
	int in;
	cin >> in;

	Board* board;
	switch (in) {
	case 1:
		board = new Board();
		board->displayBoard();
		break;
	case 2:
		board = new Board("test.txt");
		board->displayBoard();
		break;
	default:
		board = new Board();
		board->displayBoard();
		break;
	}


	bool sim = true;
	while (sim) {
		cout << "Choose an option:" << endl;
		cout << "1. Step forward" << endl;
		cout << "2. End simulation" << endl;
		cout << "3. Save current state" << endl;
		cin >> in;

		switch(in) {
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

	return 0;

}