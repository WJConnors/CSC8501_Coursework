#include <iostream>
#include <random>
#include <unordered_set>
#include "Board.h"

using namespace std;

Board::Board() :
	x_size(default_x), y_size(default_y)
{
	initializeGrid(default_alive);
}
Board::Board(int a) :
	x_size(default_x), y_size(default_y)
{
	initializeGrid(a);
}
Board::Board(int x, int y) :
	x_size(x), y_size(y)
{
	initializeGrid(default_alive);
}
Board::Board(int x, int y, int a) :
	x_size(x), y_size(y)
{
	initializeGrid(a);
}

void Board::initializeGrid(int a)
{
	grid.resize(x_size * y_size, 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, x_size * y_size - 1);

    std::unordered_set<int> alive_positions;

    while (alive_positions.size() < a)
    {
        int random_position = distrib(gen);
        if (grid[random_position] == 0)
        {
            grid[random_position] = 1;
            alive_positions.insert(random_position);
        }
    }
}

void Board::display_board()
{
    for (int i = 0; i < x_size; i++) {
        std::cout << ".";
        for (int j = 0; j < y_size; j++) {
            int index = i * y_size + j;

            if (grid[index] == 0) {
                std::cout << " .";
            }
            else {
                std::cout << " O";
            }
        }
        std::cout << " ." << std::endl;
    }
}