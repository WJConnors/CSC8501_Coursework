#include "Board.h"
 
void Board::checkStaticPatterns()
{
    checkBlock();
    checkBeehive();
}

void Board::checkBlock()
{
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            foundBlock = true;
            for (pair<int, int> coords : block()) {
                int x = i + coords.first;
                int y = j + coords.second;
                if (x >= x_size || y >= y_size) {
                    foundBlock = false;
                    break;
                }

                int curIndex = getVectorIndex(x, y);

                if (grid[curIndex] == 0) {
                    foundBlock = false;
                    break;
                }
            }
            if (foundBlock) return;
        }
    }
}

void Board::checkBeehive()
{
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            foundBeehive = true;
            for (pair<int, int> coords : beehive()) {
                int x = i + coords.first;
                int y = j + coords.second;
                if (x >= x_size || y >= y_size) {
                    foundBeehive = false;
                    break;
                }

                int curIndex = getVectorIndex(x, y);

                if (grid[curIndex] == 0) {
                    foundBeehive = false;
                    break;
                }
            }
            if (foundBeehive) return;
        }
    }
}