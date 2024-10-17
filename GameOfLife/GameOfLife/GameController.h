#pragma once
#include "Board.h"

class GameController
{
public:
	virtual void gameLoop();

protected:
	Board* board{ nullptr };

	void createBoard();
	void displayBoard() const;
	void displayBoard(vector<int> board ,int steps) const;
	void displayBoard(vector<int> grid) const;
	void displayOriginalBoard() const;
	void displayAllBoards() const;
	void simInterrupt() const;
	void checkPattern() const;
};