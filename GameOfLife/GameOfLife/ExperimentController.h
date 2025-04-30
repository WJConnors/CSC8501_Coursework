#pragma once
#include <mutex>
#include <atomic>
#include "GameController.h"

class ExperimentController : public GameController
{
public:
	ExperimentController();

	void gameLoop() override;
private:
	int experimentCounter{ 0 };

	void findPatternExperiment();
	void findLowestERN();
	void boardHandler();
	void displayAllBoards(Board& board) const;
	void displayBoard(vector<int> grid, int x_size, int y_size) const;

	int blockERN{ std::numeric_limits<int>::max() };
	int beehiveERN{ std::numeric_limits<int>::max() };
	int blinkerERN{ std::numeric_limits<int>::max() };
	int toadERN{ std::numeric_limits<int>::max() };
	int gliderERN{ std::numeric_limits<int>::max() };
	int scERN{ std::numeric_limits<int>::max() };
	int numExperiments;
	atomic<int> n;
	atomic<int> test;
	mutex mtx;

	Board* blockBoard{ nullptr };
	Board* beehiveBoard{ nullptr };
	Board* blinkerBoard{ nullptr };
	Board* toadBoard{ nullptr };
	Board* gliderBoard{ nullptr };
	Board* scBoard{ nullptr };

	bool showexperiment{ false };

};