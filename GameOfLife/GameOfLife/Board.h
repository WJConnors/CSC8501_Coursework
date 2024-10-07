#pragma once
#include <vector>

using namespace std;

class Board
{
public:
	Board();
	Board(int a);
	Board(int x, int y);
	Board(int x, int y, int a);

	int get_x_size() const { return x_size; }
	int get_y_size() const { return y_size; }

	void displayBoard();
	void updateBoard();
protected:
	const int x_size;
	const int y_size;
	vector<int> grid;

	void initializeGrid(int a);
	int getVectorIndex(int x, int y) const;
	int countAliveNeighbors(int x, int y) const;

	static const int default_x = 30;
	static const int default_y = 30;
	static const int default_alive = 25;
};