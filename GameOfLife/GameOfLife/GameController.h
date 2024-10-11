#pragma once
#include "Board.h"

class GameController
{
public:
	virtual void gameLoop();

	virtual ~GameController() = default;
protected:
	Board* board;

	void createBoard();
	void displayBoard() const;
	void displayBoard(vector<int> grid) const;
	void displayOriginalBoard() const;
	void simInterrupt() const;
};