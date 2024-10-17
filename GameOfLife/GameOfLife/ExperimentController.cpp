#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <chrono>
#include <thread>
#include "ExperimentController.h"
using namespace std;
using std::cout;

ExperimentController::ExperimentController() :
	n(0), numExperiments(1000), test(0) {}

void ExperimentController::gameLoop()
{
	cout << "Choose an option:" << endl;
	cout << "1. Experiment for a pattern" << endl;
	cout << "2. Experiment a for lowest ERN" << endl;
	int in;
	cin >> in;
	switch (in) {
	case 1:
		findPatternExperiment();
		break;
	case 2:
		findLowestERN();
		break;
	}
}

void ExperimentController::findPatternExperiment()
{
	cout << "Choose a pattern: " << endl;
	cout << "1. Block" << endl;
	cout << "2. Beehive" << endl;
	cout << "3. Blinker" << endl;
	cout << "4. Toad" << endl;
	cout << "5. Glider" << endl;
	cout << "6. LWSS" << endl;
	int choice;
	cin >> choice;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> numAlive(25, 900);

	auto start = chrono::high_resolution_clock::now();
	bool experiment{ true };
	while (experiment) {
		board = new Board(numAlive(gen));
		experimentCounter++;

		if (choice != 1) board->set_foundBlock(true);
		if (choice != 2) board->set_foundBeehive(true);
		if (choice != 3) board->set_foundBlinker (true);
		if (choice != 4) board->set_foundToad(true);
		if (choice != 5) board->set_foundGlider(true);
		if (choice != 6) board->set_foundLWSS(true);
		
		while (true) {

			if (board->get_foundBlock() && choice == 1) {
				experiment = false;
				cout << "A block pattern has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundBeehive() && choice == 2) {
				experiment = false;
				cout << "A beehive pattern has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundBlinker() && choice == 3) {
				experiment = false;
				cout << "An blinker has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundToad() && choice == 4) {
				experiment = false;
				cout << "An toad has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundGlider() && choice == 5) {
				experiment = false;
				cout << "A glider has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundLWSS() && choice == 6) {
				experiment = false;
				cout << "A LWSS has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_ended()) {
				break;
			}

			++ * board;
		}

		if (experiment) {
			delete(board);
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	displayAllBoards(*board);
	cout << "This board was experiment " << experimentCounter << endl;
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

	cout << "Choose an option: " << endl;
	cout << "1. Save board" << endl;
	cout << "2. Discard board" << endl;
	int in;
	cin >> in;
	if (in == 1) {
		string fname;
		cout << "Enter the file name: " << endl;
		cin >> fname;
		board->saveOriginalBoard(fname);
	}
}

void ExperimentController::findLowestERN() {
	cout << "Input the number of experiments to run:" << endl;
	cin >> numExperiments;	
	int numThreads{ 6 };

	auto start = chrono::high_resolution_clock::now();

	vector<thread> threads;

	for (int i = 0; i < numThreads; i++) {
		threads.push_back(thread(&ExperimentController::boardHandler, this));
	}

	for (auto& t : threads) {
		t.join();
	}

	auto end = std::chrono::high_resolution_clock::now();

	ifstream fin;
	fin.open("bestERNs.txt");
	string line;
	getline(fin, line);
	int bestBlock = stoi(line);
	getline(fin, line);
	int bestBeehive = stoi(line);
	getline(fin, line);
	int bestBlinker = stoi(line);
	getline(fin, line);
	int bestToad = stoi(line);
	getline(fin, line);
	int bestGlider = stoi(line);
	getline(fin, line);
	int bestLWSS = stoi(line);
	fin.close();

	cout << "The lowest block ERN is " << blockERN << endl;
	if (blockERN < bestBlock) {
		cout << "A new all time low" << endl;
		bestBlock = blockERN;
		blockBoard->saveOriginalBoard("BestBlock.txt");
	}
	else {
		cout << "The all time low is " << bestBlock << endl;
	}
	cout << "The lowest beehive ERN is " << beehiveERN << endl;
	if (beehiveERN < bestBeehive) {
		cout << "A new all time low" << endl;
		bestBeehive = beehiveERN;
		beehiveBoard->saveOriginalBoard("BestBeehive.txt");
	}
	else {
		cout << "The all time low is " << bestBeehive << endl;
	}
	cout << "The lowest blinker ERN is " << blinkerERN << endl;
	if (blinkerERN < bestBlinker) {
		cout << "A new all time low" << endl;
		bestBlinker = blinkerERN;
		blinkerBoard->saveOriginalBoard("BestBlinker.txt");
	}
	else {
		cout << "The all time low is " << bestBlinker << endl;
	}
	cout << "The lowest toad ERN is " << toadERN << endl;
	if (toadERN < bestToad) {
		cout << "A new all time low" << endl;
		bestToad = toadERN;
		toadBoard->saveOriginalBoard("BestToad.txt");
	}
	else {
		cout << "The all time low is " << bestToad << endl;
	}
	cout << "The lowest glider ERN is " << gliderERN << endl;
	if (gliderERN < bestGlider) {
		cout << "A new all time low" << endl;
		bestGlider = gliderERN;
		gliderBoard->saveOriginalBoard("BestGlider.txt");
	}
	else {
		cout << "The all time low is " << bestGlider << endl;
	}
	cout << "The lowest LWSS ERN is " << scERN << endl;
	if (scERN < bestLWSS) {
		cout << "A new all time low" << endl;
		bestLWSS = scERN;
		scBoard->saveOriginalBoard("BestLWSS.txt");
	}
	else {
		cout << "The all time low is " << bestLWSS << endl;
	}
	ofstream fout;
	fout.open("bestERNs.txt");
	fout << bestBlock << endl;
	fout << bestBeehive << endl;
	fout << bestBlinker << endl;
	fout << bestToad << endl;
	fout << bestGlider << endl;
	fout << bestLWSS << endl;
	fout.close();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
	cout << test << endl;

	Board* expBoards[6]{
		blockBoard,
		beehiveBoard,
		blinkerBoard,
		toadBoard,
		gliderBoard,
		scBoard
	};

	int in{ -1 };
	while(in != 0) {
		cout << "Choose an option:" << endl;
		cout << "0. End experiment" << endl;
		cout << "1. Display block" << endl;
		cout << "2. Display beehive" << endl;
		cout << "3. Display blinker" << endl;
		cout << "4. Display toad" << endl;
		cout << "5. Display glider" << endl;
		cout << "6. Display LWSS" << endl;
		cin >> in;
		if (in >= 1 && in <= 6) {
			displayAllBoards(*expBoards[in - 1]);
		}
	}

}

void ExperimentController::boardHandler()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> numAlive(25, 900);
	//uniform_int_distribution<> xDistrib(30, 50);
	//uniform_int_distribution<> yDistrib(30, 50);
	Board* board;
	while (true) {
		if (n.fetch_add(1) >= numExperiments) {
			break;
		}

		Board* tempBlockBoard{ nullptr };
		Board* tempBeehiveBoard{ nullptr };
		Board* tempBlinkerBoard{ nullptr };
		Board* tempToadBoard{ nullptr };
		Board* tempGliderBoard{ nullptr };
		Board* tempSCBoard{ nullptr };

		int tempBlock = blockERN;
		int tempBeehive = beehiveERN;
		int tempBlinker = blinkerERN;
		int tempToad = toadERN;
		int tempGlider = gliderERN;
		int tempSC = scERN;

		//board = new Board(xDistrib(gen), yDistrib(gen), numAlive(gen));
		board = new Board(numAlive(gen));
		int curERN = board->getERN();

		if (curERN > tempBlock) board->set_foundBlock(true);
		if (curERN > tempBeehive) board->set_foundBeehive(true);
		if (curERN > tempBlinker) board->set_foundBlinker(true);
		if (curERN > tempToad) board->set_foundToad(true);
		if (curERN > tempGlider) board->set_foundGlider(true);
		if (curERN > tempSC) board->set_foundLWSS(true);

		if (curERN > tempBlock && curERN > tempBeehive && curERN > tempBlinker && curERN > tempToad && curERN > tempGlider && curERN > tempSC) {
			delete(board);
			continue;
		}


		while (true) {

			if (board->get_foundBlock()) {
				if (curERN < tempBlock) {
					tempBlock = curERN;
					if (tempBlockBoard == nullptr) tempBlockBoard = new Board(*board);
				}
			}
			if (board->get_foundBeehive()) {
				if (curERN < tempBeehive) {
					tempBeehive = curERN;
					if (tempBeehiveBoard == nullptr) tempBeehiveBoard = new Board(*board);
				}
			}
			if (board->get_foundBlinker()) {
				if (curERN < tempBlinker) {
					tempBlinker = curERN;
					if (tempBlinkerBoard == nullptr) tempBlinkerBoard = new Board(*board);
				}
			}
			if (board->get_foundToad()) {
				if (curERN < tempToad) {
					tempToad = curERN;
					if (tempToadBoard == nullptr) tempToadBoard = new Board(*board);
				}
			}
			if (board->get_foundGlider()) {
				if (curERN < tempGlider) {
					tempGlider = curERN;
					if (tempGliderBoard == nullptr) tempGliderBoard = new Board(*board);
				}
			}
			if (board->get_foundLWSS()) {
				if (curERN < tempSC) {
					tempSC = curERN;
					if (tempSCBoard == nullptr) tempSCBoard = new Board(*board);
				}
			}

			if (board->get_ended()) {
				
				break;
			}
			++ * board;
		}

		{
			lock_guard<mutex> lock(mtx);
			if (tempBlockBoard != nullptr && tempBlock < blockERN) { blockERN = tempBlock; delete blockBoard; blockBoard = new Board(*tempBlockBoard); }
			if (tempBeehiveBoard != nullptr && tempBeehive < beehiveERN) { beehiveERN = tempBeehive; delete beehiveBoard; beehiveBoard = new Board(*tempBeehiveBoard); }
			if (tempBlinkerBoard != nullptr && tempBlinker < blinkerERN) { blinkerERN = tempBlinker; delete blinkerBoard; blinkerBoard = new Board(*tempBlinkerBoard); }
			if (tempToadBoard != nullptr && tempToad < toadERN) { toadERN = tempToad; delete toadBoard; toadBoard = new Board(*tempToadBoard); }
			if (tempGliderBoard != nullptr && tempGlider < gliderERN) { gliderERN = tempGlider; delete gliderBoard; gliderBoard = new Board(*tempGliderBoard); }
			if (tempSCBoard != nullptr && tempSC < scERN) { scERN = tempSC; delete scBoard; scBoard = new Board(*tempSCBoard); }
		}
		delete board;
		delete tempBlockBoard;
		delete tempBeehiveBoard;
		delete tempBlinkerBoard;
		delete tempToadBoard;
		delete tempGliderBoard;
		delete tempSCBoard;
	}
}

void ExperimentController::displayAllBoards(Board& board) const
{
	auto boards{ board.get_allBoards() };
	int steps = 1;
	for (auto& grid : boards) {
		cout << "This is the board after " << steps++ << " turns" << endl;
		displayBoard(grid, board.get_x_size(), board.get_y_size());
	}
}

void ExperimentController::displayBoard(vector<int> grid, int x_size, int y_size) const
{
	for (int i = 0; i < x_size; i++) {
		cout << ".";
		for (int j = 0; j < y_size; j++) {
			int index = i * y_size + j;
			if (grid[index] == 0) {
				cout << " .";
			}
			else {
				cout << "O.";
			}
		}
		cout << endl;
	}
}