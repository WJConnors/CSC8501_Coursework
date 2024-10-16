#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <unordered_set>
#include "Board.h"

using namespace std;

Board::Board()
{
	initializeGrid(aliveCells);
}
Board::Board(int a) :
    aliveCells(a)
{
	initializeGrid(aliveCells);
}
Board::Board(int x, int y) :
    x_size(x), y_size(y)
{
	initializeGrid(aliveCells);
}
Board::Board(int x, int y, int a) :
    x_size(x), y_size(y), aliveCells(a)
{
	initializeGrid(aliveCells);
}

Board::Board(string fpath)
{
    ifstream fin;
    fin.open(fpath);
    string line;

    getline(fin, line);
    stepsTaken = stoi(line);
    getline(fin, line);
    x_size = stoi(line);
    getline(fin, line);
    y_size = stoi(line);

    grid.resize(static_cast<size_t>(x_size) * static_cast<size_t>(y_size), 0);

    while (getline(fin, line)) {
        int x, y;
        istringstream coords(line);
        coords >> x >> y;
        int curIndex = getVectorIndex(x, y);
        grid[curIndex] = 1;
        aliveCells++;
    }

    originalGrid = grid;

    checkStaticPatterns();
    checkOscillators();
    checkSpaceShips();
}

void Board::initializeGrid(int a)
{
    grid.resize(static_cast<size_t>(x_size) * static_cast<size_t>(y_size), 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, x_size * y_size - 1);

    std::unordered_set<int> alive_positions;

    while (alive_positions.size() < a) {
        int random_position = distrib(gen);
        if (grid[random_position] == 0) {
            grid[random_position] = 1;
            alive_positions.insert(random_position);
        }
    }
    originalGrid = grid;
    storedGrids.push_back(grid);

    checkStaticPatterns();
    checkOscillators();
    checkSpaceShips();
}

int Board::getVectorIndex(int x, int y) const
{
    if (x < 0 || x >= x_size || y < 0 || y >= y_size) {
        return -1;
    }
    return x * y_size + y;
}

int Board::countAliveNeighbors(int x, int y) const
{
    int alive_neighbors = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int neighbor_x{ x + i };
            int neighbor_y{ y + j };
            int neighbor_index{ getVectorIndex(neighbor_x, neighbor_y) };
            if (neighbor_index != -1 && grid[neighbor_index] == 1) alive_neighbors++;
        }
    }
    return alive_neighbors;
}

void Board::operator++()
{
    vector<int> newGrid = grid;
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            int neighbours{ countAliveNeighbors(i, j) };
            int curIndex{ getVectorIndex(i, j) };
            if (grid[curIndex] == 0) {
                if (neighbours == 3) {
                    newGrid[curIndex] = 1;
                    aliveCells++;
                }
            }
            else if (neighbours < 2 || neighbours > 3) {
                newGrid[curIndex] = 0;
                aliveCells--;
            }
        }
    }
    
    if (aliveCells == 0 || grid == newGrid) ended = true;
    grid = newGrid;
    for (vector<int> tempGrid : storedGrids) {
        if (tempGrid == grid) {
            ended = true;
            break;
        }
    }
    storedGrids.push_back(grid);
    stepsTaken++;
    checkStaticPatterns();
    checkOscillators();
    checkSpaceShips();
}

void Board::saveBoard(string fpath) const { saver(fpath, false); }
void Board::saveOriginalBoard(string fpath) const { saver(fpath, true); }

void Board::saver(string fpath, bool original) const
{
    vector<int> grid;
    int stepsTaken;
    if (original) {
        grid = originalGrid;
        stepsTaken = 0;
    }
    else {
        grid = this->grid;
        stepsTaken = this->stepsTaken;
    }
    ofstream fout;
    fout.open(fpath);
    fout << stepsTaken << endl;
    fout << x_size << endl;
    fout << y_size << endl;
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            int curIndex = getVectorIndex(i, j);
            if (grid[curIndex] == 1) {
                fout << i << " " << j << endl;
            }
        }
    }
    fout.close();
}