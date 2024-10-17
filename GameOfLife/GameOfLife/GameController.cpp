#include <iostream>
#include "GameController.h"

using namespace std;

void GameController::createBoard()
{
    cout << "Choose an option:" << endl;
    cout << "1. Create a new board" << endl;
    cout << "2. Load a saved board" << endl;
    int in;
    cin >> in;

    switch (in) {
    case 1:
        board = new Board();
        displayBoard();
        break;
    case 2:
        string fname;
        cout << "Enter the file name: " << endl;
        cin >> fname;
        board = new Board(fname);
        displayBoard();
        cout << board->getERN();
        break;
    }
}

void GameController::gameLoop()
{
    createBoard();
    checkPattern();
    bool loop{ true };
    int in;
    while (loop) {

        bool sim{ true };
        while (sim) {
            cout << "Choose an option:" << endl;
            cout << "1. Step forward" << endl;
            cout << "2. End simulation" << endl;
            cout << "3. Save current state" << endl;
            cout << "4. Look for specific pattern" << endl;
            cin >> in;

            switch (in) {
            case 1:
                ++*board;
                displayBoard();
                checkPattern();
                break;
            case 2:
                sim = false;
                break;
            case 3:
            {
                string fname;
                cout << "Enter the file name: " << endl;
                cin >> fname;
                board->saveBoard(fname);
                break;
            }
            case 4:
                cout << "Choose a pattern" << endl;
                cout << "1. Block" << endl;
                cout << "2. Beehive" << endl;
                cout << "3. Blinker" << endl;
                cout << "4. Toad" << endl;
                cout << "5. Glider" << endl;
                cout << "6. LWSS" << endl;
                int choice;
                cin >> choice;

                while (true) {
                    if (choice == 1 && board->get_foundBlock()) break;
                    if (choice == 2 && board->get_foundBeehive()) break;
                    if (choice == 3 && board->get_foundBlinker()) break;
                    if (choice == 4 && board->get_foundToad()) break;
                    if (choice == 5 && board->get_foundGlider()) break;
                    if (choice == 6 && board->get_foundLWSS()) break;
                    if (board->get_ended()) break;
                    ++*board;
                }
                displayAllBoards();
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
        {
            string fname;
            cout << "Enter the file name: " << endl;
            cin >> fname;
            board->saveBoard(fname);
            break;
        }
        case 2:
        {
            string fname;
            cout << "Enter the file name: " << endl;
            cin >> fname;
            board->saveOriginalBoard(fname);
            break;
        }
        case 3:
            displayAllBoards();
            break;
        }
    }
}

void GameController::checkPattern() const
{
    if (board->get_foundBlock() || board->get_foundBeehive()) {
        cout << "A static pattern has been found" << endl;
    }
    if (board->get_foundBlinker() || board->get_foundToad()) {
        cout << " An oscillator has been found" << endl;
    }
    if (board->get_foundGlider() || board->foundLWSS) {
        cout << "A spaceship has been found during experiment " << endl;
    }
}