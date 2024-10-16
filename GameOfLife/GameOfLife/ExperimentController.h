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

	int blockERN{ std::numeric_limits<int>::max() };
	int beehiveERN{ std::numeric_limits<int>::max() };
	int blinkerERN{ std::numeric_limits<int>::max() };
	int toadERN{ std::numeric_limits<int>::max() };
	int gliderERN{ std::numeric_limits<int>::max() };
	int scERN{ std::numeric_limits<int>::max() };
	int numExperiments;
	atomic<int> n;
	mutex mtx;
};