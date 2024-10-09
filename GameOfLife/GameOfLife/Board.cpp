#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <unordered_set>
#include "Board.h"

using namespace std;

void Board::gameLoop()
{
    bool loop{ true };
    while (loop) {
        cout << "Choose an option:" << endl;
        cout << "1. Create a new board" << endl;
        cout << "2. Load the saved board" << endl;
        int in;
        cin >> in;

        switch (in) {
        case 1:
            setupBoard();
            displayBoard();
            break;
        case 2:
            setupBoard("test.txt");
            displayBoard();
            break;
        default:
            setupBoard();
            displayBoard();
            break;
        }

        bool sim{ true };
        while (sim) {
            cout << "Choose an option:" << endl;
            cout << "1. Step forward" << endl;
            cout << "2. End simulation" << endl;
            cout << "3. Save current state" << endl;
            cin >> in;

            switch (in) {
            case 1:
                updateBoard();
                displayBoard();
                break;
            case 2:
                sim = false;
                break;
            case 3:
                saveBoard("test.txt");
                break;
            }
        }

        displayOriginalBoard();

        cout << "Choose an option:" << endl;
        cout << "1. Start a new simulation" << endl;
        cout << "2. Exit the program" << endl;
        cin >> in;

        switch (in) {
        case 2:
            loop = false;
        }
    }
}

void Board::setupBoard()
{
    x_size = default_x;
    y_size = default_y;
    stepsTaken = 0;
	initializeGrid(default_alive);
}
void Board::setupBoard(int a)
{
    x_size = default_x;
    y_size = default_y;
    stepsTaken = 0;
	initializeGrid(a);
}
void Board::setupBoard(int x, int y)
{
    x_size = x;
    y_size = y;
    stepsTaken = 0;
	initializeGrid(default_alive);
}
void Board::setupBoard(int x, int y, int a)
{
    x_size = x;
    y_size = y;
    stepsTaken = 0;
	initializeGrid(a);
}

void Board::setupBoard(string fpath)
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
    }

    originalGrid = grid;
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
}

void Board::displayBoard() const
{
    cout << "This is the board after " << stepsTaken << " turns" << endl;
    displayBoard(grid);
}

void Board::displayOriginalBoard() const
{
    cout << "This is the original board" << endl;
    displayBoard(originalGrid);
}

void Board::displayBoard(vector<int> grid) const
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

void Board::updateBoard()
{
    vector<int> newGrid = grid;
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            int neighbours{ countAliveNeighbors(i, j) };
            int curIndex{ getVectorIndex(i, j) };
            if (grid[curIndex] == 0) {
                if (neighbours == 3) newGrid[curIndex] = 1;
            }
            else if (neighbours < 2 || neighbours > 3) newGrid[curIndex] = 0;
        }
    }
    grid = newGrid;
    stepsTaken++;
}

void Board::saveBoard(string fpath) const
{
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