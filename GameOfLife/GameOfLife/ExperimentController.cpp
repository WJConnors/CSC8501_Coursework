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
	displayAllBoards();
}

void ExperimentController::findLowestERN() {
	cout << "Input the number of experiments to run:" << endl;
	cin >> numExperiments;	
	int numThreads{ 8 };

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
}

void ExperimentController::boardHandler()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> numAlive(25, 900);
	//uniform_int_distribution<> distribXY(30, 50);
	Board* board;
	while (true) {
		if (n.fetch_add(1) >= numExperiments) {
			break;
		}

		int tempBlock = blockERN;
		int tempBeehive = beehiveERN;
		int tempBlinker = blinkerERN;
		int tempToad = toadERN;
		int tempGlider = gliderERN;
		int tempSC = scERN;

		//board = new Board(distribXY(gen), distribXY(gen), numAlive(gen));
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

			if (board->get_foundBlock()) { if (curERN < tempBlock) tempBlock = curERN; }
			if (board->get_foundBeehive()) { if (curERN < tempBeehive) tempBeehive = curERN; }
			if (board->get_foundBlinker()) { if (curERN < tempBlinker) tempBlinker = curERN; }
			if (board->get_foundToad()) { if (curERN < tempToad) tempToad = curERN; }
			if (board->get_foundGlider()) { if (curERN < tempGlider) tempGlider = curERN; }
			if (board->get_foundLWSS()) { if (curERN < tempSC) tempSC = curERN; }

			if (board->get_ended()) {
				delete(board);
				break;
			}
			++ * board;
		}

		{
			lock_guard<mutex> lock(mtx);
			if (tempBlock < blockERN) blockERN = tempBlock;
			if (tempBeehive < beehiveERN) beehiveERN = tempBeehive;
			if (tempBlinker < blinkerERN) blinkerERN = tempBlinker;
			if (tempToad < toadERN) toadERN = tempToad;
			if (tempGlider < gliderERN) gliderERN = tempGlider;
			if (tempSC < scERN) scERN = tempSC;
		}
	}
}