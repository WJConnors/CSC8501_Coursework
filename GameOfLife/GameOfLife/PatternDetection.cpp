#include "Board.h"

using namespace Patterns;
 
void Board::checkStaticPatterns()
{
    foundBlock = checkPattern(block, block_x_size, block_y_size).first;
    foundBeehive = checkPattern(beehive, beehive_x_size, beehive_y_size).first;
    foundBeehive = checkPattern(rotatedBeeHive, rotated_beehive_x_size, rotated_beehive_y_size).first;
}

void Board::checkOscillators()
{
    switch (bc.versionFound) {
    case 0:
    {
        auto result = checkPattern(blinker1, blinker_x_size, blinker_y_size);
        if (result.first) {
            bc.versionFound = 1;
            bc.x = result.second.first;
            bc.y = result.second.second;
        }
        else {
            result = checkPattern(blinker2, blinker_x_size, blinker_y_size);
            if (result.first) {
                bc.versionFound = 2;
                bc.x = result.second.first;
                bc.y = result.second.second;
            }
        }
        break;
    }
    case 1:
    {
        auto result = checkPattern(blinker2, blinker_x_size, blinker_y_size);
        if (result.first && result.second.first == bc.x && result.second.second == bc.y) {
            foundBlinker = true;
            bc.versionFound = 2;
        }
        break;
    }
    case 2:
    {
        auto result = checkPattern(blinker1, blinker_x_size, blinker_y_size);
        if (result.first && result.second.first == bc.x && result.second.second == bc.y) {
            foundBlinker = true;
            bc.versionFound = 1;
        }
        break;
    }
    }
}

template <size_t N>
pair<bool, pair<int, int>> Board::checkPattern(const int(&pattern)[N], int pattern_x_size, int pattern_y_size)
{
    bool foundPattern{ true };
    for (int i = 0; i < x_size - pattern_x_size; i++) {
        for (int j = 0; j < y_size - pattern_y_size; j++) {
            foundPattern = true;
            for (int x = 0; x < pattern_x_size; x++) {
                for (int y = 0; y < pattern_y_size; y++) {
                    int curX = i + x;
                    int curY = j + y;
                    if (curX >= x_size || curY >= y_size) {
                        foundPattern = false;
                        break;
                    }

                    int curIndex = getVectorIndex(curX, curY);
                    int curPatternIndex = x * pattern_y_size + y;

                    if (grid[curIndex] != pattern[curPatternIndex]) {
                        foundPattern = false;
                        break;
                    }
                }
            }
            if (foundPattern) return make_pair(true, make_pair(i, j));
        }
    }
    return make_pair(false, make_pair(-1, -1));
}