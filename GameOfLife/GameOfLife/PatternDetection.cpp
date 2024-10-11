#include "Board.h"

 
void Board::checkStaticPatterns()
{
    foundBlock = checkPattern(block, block_x_size, block_y_size);
    foundBeehive = checkPattern(beehive, beehive_x_size, beehive_y_size);
    foundBeehive = checkPattern(rotatedBeeHive, rotated_beehive_x_size, rotated_beehive_y_size);
}
template <size_t N>
bool Board::checkPattern(const int(&pattern)[N], int pattern_x_size, int pattern_y_size)
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
            if (foundPattern) return true;
        }
    }
    return false;
}