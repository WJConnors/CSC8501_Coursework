#pragma once
#include <vector>
#include <string>
#include "Patterns.h"

using namespace std;

class Board
{
public:
	Board();
	Board(int a);
	Board(int x, int y);
	Board(int x, int y, int a);
	Board(string fpath);

	int get_x_size() const { return x_size; }
	int get_y_size() const { return y_size; }
	int getERN() const { return startingERN; }
	int get_stepsTaken() const { return stepsTaken; }
	int get_aliveCells() const { return aliveCells; }
	bool get_ended() const { return ended; }
	bool get_foundBlock() const { return foundBlock; }
	bool get_foundBeehive() const { return foundBeehive; }
	bool get_foundBlinker() const { return foundBlinker; }
	bool get_foundToad() const { return foundToad; }
	bool get_foundGlider() const { return foundGlider; }
	bool get_foundLWSS() const { return foundLWSS; }
	void set_foundBlock(bool b) { foundBlock = b; }
	void set_foundBeehive(bool b) { foundBeehive = b; }
	void set_foundBlinker(bool b) { foundBlinker = b; }
	void set_foundToad(bool b) { foundToad = b; }
	void set_foundGlider(bool b) { foundGlider = b; }
	void set_foundLWSS(bool b) { foundLWSS = b; }
	vector<vector<int>> get_allBoards() const { return storedGrids; }
	vector<int> get_grid() const { return grid; }
	vector<int> get_originalGrid() const { return originalGrid; }

private:
	int x_size{ default_x };
	int y_size{ default_y };
	int startingERN;
	vector<int> grid;
	vector<int> originalGrid;
	vector<vector<int>> storedGrids{};
	int stepsTaken{ 0 };
	int aliveCells{ default_alive };
	bool ended{ false };
	bool foundBlock{ false };
	bool foundBeehive{ false };
	bool foundBlinker{ false };
	bool foundToad{ false };
	bool foundGlider{ false };
	bool foundLWSS{ false };

	struct OscCheck {
		int versionFound{ 0 }; //0 for nothing found, 1 for variation 1, 2 for variation 2
		int x{ -1 };
		int y{ -1 };
	};
	OscCheck bc;
	OscCheck tc1;
	OscCheck tc2;

	struct SpaceShipCheck {
		int versionFound{ -1 };
		int stepCount{ 0 };
		int x{ -1 };
		int y{ -1 };
	};
	SpaceShipCheck gc1;
	SpaceShipCheck gc2;
	SpaceShipCheck gc3;
	SpaceShipCheck gc4;

	SpaceShipCheck lwss1;
	SpaceShipCheck lwss2;
	SpaceShipCheck lwss3;
	SpaceShipCheck lwss4;

	void initializeGrid(int a);
	void calculateERN();

	void operator++();

	void saveBoard(string fpath) const;
	void saveOriginalBoard(string fpath) const;
	void saver(string fpath, bool original) const;

	int getVectorIndex(int x, int y) const;
	int countAliveNeighbors(int x, int y) const;

	void checkStaticPatterns();
	pair<bool, pair<int, int>> checkPattern(const int* pattern, int pattern_x_size, int pattern_y_size);

	void checkOscillators();
	template <size_t N>
	bool checkOscillator(const int(&pattern1)[N], const int(&pattern2)[N], int pattern_size, OscCheck& oc);

	void checkSpaceShips();
	bool checkSpaceShip(const int* const patterns[4], int pattern_x_size, int pattern_y_size, SpaceShipCheck& sc, const pair<int, int> scMovement[4]);

	static const int default_x = 30;
	static const int default_y = 30;
	static const int default_alive = 25;

	friend class GameController;
	friend class ExperimentController;
};