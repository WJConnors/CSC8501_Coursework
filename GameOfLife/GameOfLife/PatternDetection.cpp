#include "Board.h"
#include <iostream>
 
void Board::checkStaticPatterns()
{
    checkBlock();
    checkBeehive();
}

void Board::checkBlock()
{
    int block[16]{
        0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0
    };
    int block_x_size = 4;
    int block_y_size = 4;
    for (int i = 0; i < x_size - block_x_size; i++) {
        for (int j = 0; j < y_size - block_y_size; j++) {
            foundBlock = true;
            for (int x = 0; x < block_x_size; x++) {
                for (int y = 0; y < block_y_size; y++) {
                    int curX = i + x;
                    int curY = j + y;
                    if (curX >= x_size || curY >= y_size) {
                        foundBlock = false;
                        break;
                    }

                    int curIndex = getVectorIndex(curX, curY);
                    int curBlockIndex = x * block_y_size + y;

                    if (grid[curIndex] != block[curBlockIndex]) {
                        foundBlock = false;
                        break;
                    }
                }
            }
            if (foundBlock) {
                std::cout << "found block" << std::endl;
                return;
            }
        }
    }
}

void Board::checkBeehive()
{
    int beehive[30]{
        0,0,0,0,0,0,
        0,0,1,1,0,0,
        0,1,0,0,1,0,
        0,0,1,1,0,0,
        0,0,0,0,0,0
    };
    int beehive_x_size = 5;
    int beehive_y_size = 6;
    for (int i = 0; i < x_size - beehive_x_size; i++) {
        for (int j = 0; j < y_size - beehive_y_size; j++) {
            foundBeehive = true;
            for (int x = 0; x < beehive_x_size; x++) {
                for (int y = 0; y < beehive_y_size; y++) {
                    int curX = i + x;
                    int curY = j + y;
                    if (curX >= x_size || curY >= y_size) {
                        foundBeehive = false;
                        break;
                    }

                    int curIndex = getVectorIndex(curX, curY);
                    int curBlockIndex = x * beehive_y_size + y;

                    if (grid[curIndex] != beehive[curBlockIndex]) {
                        foundBeehive = false;
                        break;
                    }
                }
            }
            if (foundBeehive) {
                std::cout << "found beehive" << std::endl;
                return;
            }
        }
    }
}