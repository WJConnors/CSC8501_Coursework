#include <iostream>
#include <random>
#include <limits>
#include <chrono>
#include <thread>
#include "ExperimentController.h"
using namespace std;
using std::cout;

ExperimentController::ExperimentController() :
	n(0), numExperiments(1000) {}

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
	cout << "Input board x size, y size, and number of starting alive cells:" << endl;
	int x, y, a;
	cin >> x;
	cin >> y;
	cin >> a;
	bool experiment{ true };
	while (experiment) {
		board = new Board(x, y, a);
		experimentCounter++;

		while (true) {

			if (board->get_foundBlock() || board->get_foundBeehive()) {
				experiment = false;
				cout << "A static pattern has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundBlinker() || board->get_foundToad()) {
				experiment = false;
				cout << "An oscillator has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_foundGlider() || board->foundLWSS) {
				experiment = false;
				cout << "A spaceship has been found during experiment " << experimentCounter << endl;
				break;
			}

			if (board->get_ended() || board->foundLWSS) {
				break;
			}

			++ * board;
		}

		if (experiment) {
			delete(board);
		}
	}
	displayAllBoards(*board);
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

	cout << "The lowest block ERN is " << blockERN << endl;
	cout << "The lowest beehive ERN is " << beehiveERN << endl;
	cout << "The lowest blinker ERN is " << blinkerERN << endl;
	cout << "The lowest toad ERN is " << toadERN << endl;
	cout << "The lowest glider ERN is " << gliderERN << endl;
	cout << "The lowest LWSS ERN is " << scERN << endl;

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

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

		board = new Board(numAlive(gen));
		int curERN = board->getERN();

		if (curERN > blockERN && curERN > beehiveERN && curERN > blinkerERN && curERN > toadERN && curERN > gliderERN && curERN > scERN) {
			delete(board);
			continue;
		}
		if (curERN > blockERN) board->set_foundBlock(true);
		if (curERN > beehiveERN) board->set_foundBeehive(true);
		if (curERN > blinkerERN) board->set_foundBlinker(true);
		if (curERN > toadERN) board->set_foundToad(true);
		if (curERN > gliderERN) board->set_foundGlider(true);
		if (curERN > scERN) board->set_foundLWSS(true);

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
			if (tempBlockBoard != nullptr) { blockERN = tempBlock; delete blockBoard; blockBoard = new Board(*tempBlockBoard); }
			if (tempBeehiveBoard != nullptr) { beehiveERN = tempBeehive; delete beehiveBoard; beehiveBoard = new Board(*tempBeehiveBoard); }
			if (tempBlinkerBoard != nullptr) { blinkerERN = tempBlinker; delete blinkerBoard; blinkerBoard = new Board(*tempBlinkerBoard); }
			if (tempToadBoard != nullptr) { toadERN = tempToad; delete toadBoard; toadBoard = new Board(*tempToadBoard); }
			if (tempGliderBoard != nullptr) { gliderERN = tempGlider; delete gliderBoard; gliderBoard = new Board(*tempGliderBoard); }
			if (tempSCBoard != nullptr) { scERN = tempSC; delete scBoard; scBoard = new Board(*tempSCBoard); }
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