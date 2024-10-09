#pragma once
#include "Board.h"

class GameController
{
public:
	GameController();
	void gameLoop();
protected:
	Board* board;

	void createBoard();
	void displayBoard() const;
	void displayBoard(vector<int> grid) const;
	void displayOriginalBoard() const;
};