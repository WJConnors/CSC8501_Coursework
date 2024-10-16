#pragma once
#include "GameController.h"

class ExperimentController : public GameController
{
public:
	void gameLoop() override;
private:
	int experimentCounter{ 0 };

	void findPatternExperiment();
	void findLowestERN();
};