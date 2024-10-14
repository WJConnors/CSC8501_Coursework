#include <iostream>
#include "GameController.h"

using namespace std;

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
    createBoard();

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
                ++*board;
                displayBoard();
                if (board->get_foundBlock() || board->get_foundBeehive()) {
                    cout << "A static pattern has been found" << endl;
                }
                if (board->get_foundBlinker() || board->get_foundToad()) {
                    cout << " An oscillator has been found" << endl;
                }
                break;
            case 2:
                sim = false;
                break;
            case 3:
                board->saveBoard("test.txt");
                break;
            }

            if (board->get_ended()) {
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

void GameController::displayBoard(vector<int> board, int steps) const
{
    cout << "This is the board after " << steps << " turns" << endl;
    displayBoard(board);
}

void GameController::displayOriginalBoard() const
{
    cout << "This is the original board" << endl;
    displayBoard(board->get_originalGrid());
}

void GameController::displayAllBoards() const
{
    auto boards{ board->get_allBoards() };
    int steps = 1;
    for (auto& board : boards) {
        displayBoard(board, steps++);
    }
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
    int in{ 0 };
    while (in != 4) {
        cout << "The simulation has concluded. Choose an option" << endl;
        cout << "1. Save the current board" << endl;
        cout << "2. Save the original board" << endl;
        cout << "3. View every step from the beginning" << endl;
        cout << "4. Discard the current board" << endl;
        int in;
        cin >> in;

        switch (in)
        {
        case 1:
            board->saveBoard("test.txt");
            break;
        case 2:
            board->saveOriginalBoard("test.txt");
            break;
        case 3:
            displayAllBoards();
            break;
        }
    }
}