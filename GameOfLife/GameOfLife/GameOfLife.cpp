#include <iostream>
#include "GameController.h"
#include "ExperimentController.h"

using namespace std;

int main()
{
	ExperimentController ec = ExperimentController();
	ec.gameLoop();

	return 0;

}