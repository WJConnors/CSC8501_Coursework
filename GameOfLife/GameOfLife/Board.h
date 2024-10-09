#pragma once
#include <vector>
#include <string>

using namespace std;

class Board
{
public:
	Board();
	Board(int a);
	Board(int x, int y);
	Board(int x, int y, int a);
	Board(string fpath);

protected:
	int x_size{ default_x };
	int y_size{ default_y };
	vector<int> grid;
	vector<int> originalGrid;
	int stepsTaken{ 0 };
	int aliveCells{ default_alive };
	bool ended{ false };

	int get_x_size() const { return x_size; }
	int get_y_size() const { return y_size; }
	int get_stepsTaken() const { return stepsTaken; }
	int get_aliveCells() const { return aliveCells; }
	bool get_ended() const { return ended; }
	vector<int> get_grid() const { return grid; }
	vector<int> get_originalGrid() const { return originalGrid; }

	void initializeGrid(int a);

	void updateBoard();

	void saveBoard(string fpath) const;

	int getVectorIndex(int x, int y) const;
	int countAliveNeighbors(int x, int y) const;

	static const int default_x = 30;
	static const int default_y = 30;
	static const int default_alive = 25;

	friend class GameController;
};