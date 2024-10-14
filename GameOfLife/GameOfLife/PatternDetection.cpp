#include "Board.h"

using namespace Patterns;

void Board::checkStaticPatterns()
{
    foundBlock = checkPattern(block, block_x_size, block_y_size).first;
    foundBeehive = checkPattern(beehive1, beehive1_x_size, beehive1_y_size).first;
    foundBeehive = checkPattern(beehive2, beehive2_x_size, beehive2_y_size).first;
}

void Board::checkOscillators()
{
    foundBlinker = checkOscillator(blinker1, blinker2, blinker_size, bc);
    bool foundToad1 = checkOscillator(toad1_1, toad1_2, toad_size, tc1);
    bool foundToad2 = checkOscillator(toad2_1, toad2_2, toad_size, tc2);
    if (foundToad1 || foundToad2) foundToad = true;
}

template <size_t N>
bool Board::checkOscillator(const int(&pattern1)[N], const int(&pattern2)[N], int pattern_size, OscCheck& oc)
{
    switch (oc.versionFound) {
    case 0:
    {
        auto result = checkPattern(pattern1, pattern_size, pattern_size);
        if (result.first) {
            oc.versionFound = 1;
            oc.x = result.second.first;
            oc.y = result.second.second;
        }
        else {
            result = checkPattern(pattern2, pattern_size, pattern_size);
            if (result.first) {
                oc.versionFound = 2;
                oc.x = result.second.first;
                oc.y = result.second.second;
            }
        }
        break;
    }
    case 1:
    {
        auto result = checkPattern(pattern2, pattern_size, pattern_size);
        if (result.first && result.second.first == oc.x && result.second.second == oc.y) {
            oc.versionFound = 2;
            return true;

        }
        break;
    }
    case 2:
    {
        auto result = checkPattern(pattern1, pattern_size, pattern_size);
        if (result.first && result.second.first == oc.x && result.second.second == oc.y) {
            oc.versionFound = 1;
            return true;
        }
        break;
    }
    }
    return false;
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
            if (foundPattern) {
                return make_pair(true, make_pair(i, j));
            }
        }
    }
    return make_pair(false, make_pair(-1, -1));
}