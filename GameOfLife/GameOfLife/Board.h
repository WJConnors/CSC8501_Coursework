#pragma once
#include <vector>
#include <string>
#include <array>

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
	int get_stepsTaken() const { return stepsTaken; }
	int get_aliveCells() const { return aliveCells; }
	bool get_ended() const { return ended; }
	bool get_foundBlock() const { return foundBlock; }
	bool get_foundBeehive() const { return foundBeehive; }
	vector<int> get_grid() const { return grid; }
	vector<int> get_originalGrid() const { return originalGrid; }

private:
	int x_size{ default_x };
	int y_size{ default_y };
	vector<int> grid;
	vector<int> originalGrid;
	vector<vector<int>> storedGrids{};
	int stepsTaken{ 0 };
	int aliveCells{ default_alive };
	bool ended{ false };
	bool foundBlock{ false };
	bool foundBeehive{ false };

	void initializeGrid(int a);

	void updateBoard();

	void saveBoard(string fpath) const;
	void saveOriginalBoard(string fpath) const;
	void saver(string fpath, bool original) const;

	int getVectorIndex(int x, int y) const;
	int countAliveNeighbors(int x, int y) const;

	void checkStaticPatterns();
	template <size_t N>
	bool checkPattern(const int(&pattern)[N], int pattern_x_size, int pattern_y_size);

	static const int default_x = 30;
	static const int default_y = 30;
	static const int default_alive = 25;

	friend class GameController;
	friend class ExperimentController;

	// ================= Patterns =================

	int block_x_size{ 4 };
	int block_y_size{ 4 };
	int block[16]{
	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0
	};

	int beehive_x_size = 5;
	int beehive_y_size = 6;
	int beehive[30]{
	 0,0,0,0,0,0,
	 0,0,1,1,0,0,
	 0,1,0,0,1,0,
	 0,0,1,1,0,0,
	 0,0,0,0,0,0
	};

	int rotated_beehive_x_size = 6;
	int rotated_beehive_y_size = 5;
	int rotatedBeeHive[30]{
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	};

};