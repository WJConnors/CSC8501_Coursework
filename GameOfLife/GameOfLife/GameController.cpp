#include <iostream>
#include "GameController.h"

using namespace std;

GameController::GameController()
{
    createBoard();
}

void GameController::createBoard()
{
    cout << "Choose an option:" << endl;
    cout << "1. Create a new board" << endl;
    cout << "2. Load the saved board" << endl;
    int in;
    cin >> in;

    switch (in) {
    case 1:
        board = new Board();
        displayBoard();
        break;
    case 2:
        board = new Board("test.txt");
        displayBoard();
        break;
    }
}

void GameController::gameLoop()
{
    bool loop{ true };
    int in;
    while (loop) {

        bool sim{ true };
        while (sim) {
            cout << "Choose an option:" << endl;
            cout << "1. Step forward" << endl;
            cout << "2. End simulation" << endl;
            cout << "3. Save current state" << endl;
            cin >> in;

            switch (in) {
            case 1:
                board->updateBoard();
                displayBoard();
                break;
            case 2:
                sim = false;
                break;
            case 3:
                board->saveBoard("test.txt");
                break;
            }

            if (board->get_aliveCells() == 0) {
                simInterrupt();
                sim = false;
            }
        }

        displayOriginalBoard();
        delete(board);

        cout << "Choose an option:" << endl;
        cout << "1. Start a new simulation" << endl;
        cout << "2. Exit the program" << endl;
        cin >> in;

        switch (in) {
        case 1:
            createBoard();
            break;
        case 2:
            loop = false;
            break;
        }
    }
}

void GameController::displayBoard() const
{
    cout << "This is the board after " << board->get_stepsTaken() << " turns" << endl;
    displayBoard(board->get_grid());
}

void GameController::displayOriginalBoard() const
{
    cout << "This is the original board" << endl;
    displayBoard(board->get_originalGrid());
}

void GameController::displayBoard(vector<int> grid) const
{
    int x_size{ board->get_x_size() };
    int y_size{ board->get_y_size() };
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

void GameController::simInterrupt() const
{
    cout << "The simulation has concluded. Choose an option" << endl;
    cout << "1. Save the current board" << endl;
    cout << "2. Discard the current board" << endl;
    int in;
    cin >> in;

    switch (in)
    {
    case 1:
        board->saveBoard("test.txt");
        break;
    }
}