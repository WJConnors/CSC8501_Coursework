#pragma once
#include <vector>
#include <string>

using namespace std;

class Board
{
public:
	void gameLoop();

protected:
	int x_size;
	int y_size;
	vector<int> grid;
	vector<int> originalGrid;
	int stepsTaken;

	int get_x_size() const { return x_size; }
	int get_y_size() const { return y_size; }

	void setupBoard();
	void setupBoard(int a);
	void setupBoard(int x, int y);
	void setupBoard(int x, int y, int a);
	void setupBoard(string fpath);

	void displayBoard() const;
	void saveBoard(string fpath) const;
	void displayOriginalBoard();
	void updateBoard();

	void initializeGrid(int a);
	void displayBoard(vector<int> grid) const;
	int getVectorIndex(int x, int y) const;
	int countAliveNeighbors(int x, int y) const;

	static const int default_x = 30;
	static const int default_y = 30;
	static const int default_alive = 25;
};