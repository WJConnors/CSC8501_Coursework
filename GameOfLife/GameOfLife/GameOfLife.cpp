#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board* board{ new Board() };

	board->gameLoop();

	delete(board);

	return 0;

}