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

		GameController* gc{ nullptr };

		switch (in) {
		case 1:
		{
			gc = new GameController();
			break;
		}
		case 2:
		{
			gc = new ExperimentController();
			break;
		}
		}
		if (gc != nullptr) {
			gc->gameLoop();
			delete(gc);
		}

	}

	return 0;

}