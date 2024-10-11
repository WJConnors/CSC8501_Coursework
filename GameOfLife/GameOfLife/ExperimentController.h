#pragma once
#include "GameController.h"

class ExperimentController : public GameController
{
public:
	ExperimentController();
	void gameLoop() override;
private:
	void createBoard() override;
};