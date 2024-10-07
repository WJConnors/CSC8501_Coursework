#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board board = Board();
	board.displayBoard();
	board.updateBoard();
	cout << endl;
	board.displayBoard();
}