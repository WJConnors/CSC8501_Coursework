#include <iostream>
#include "GameController.h"
#include "ExperimentController.h"

using namespace std;

int main()
{
	//GameController gc = GameController();
	//gc.gameLoop();

	ExperimentController ec = ExperimentController();
	ec.gameLoop();

	return 0;

}