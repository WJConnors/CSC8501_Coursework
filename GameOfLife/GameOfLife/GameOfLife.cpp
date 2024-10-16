#include <iostream>
#include "GameController.h"
#include "ExperimentController.h"

using namespace std;

int main()
{
	int in{ -1 };
	while (in != 3) {
		cout << "Choose an option:" << endl;
		cout << "1. Look at and step through individually generated and loaded boards" << endl;
		cout << "2. Run an experiment" << endl;
		cout << "3. Close the program" << endl;
		cin >> in;

		switch (in) {
		case 1:
		{
			GameController gc = GameController();
			gc.gameLoop();
			break;
		}
		case 2:
		{
			ExperimentController* ec = new ExperimentController();
			ec->gameLoop();
			delete(ec);
			break;
		}
		}		
	}

	return 0;

}