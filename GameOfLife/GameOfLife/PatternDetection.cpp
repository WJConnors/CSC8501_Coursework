#include "Board.h"

using namespace Patterns;

void Board::checkStaticPatterns()
{
    /*
    foundBlock = checkPattern(block, block_x_size, block_y_size).first;
    foundBeehive = checkPattern(beehive1, beehive1_x_size, beehive1_y_size).first;
    foundBeehive = checkPattern(beehive2, beehive2_x_size, beehive2_y_size).first;
    */
}

void Board::checkOscillators()
{
    /*
    foundBlinker = checkOscillator(blinker1, blinker2, blinker_size, bc);
    bool foundToad1 = checkOscillator(toad1_1, toad1_2, toad_size, tc1);
    bool foundToad2 = checkOscillator(toad2_1, toad2_2, toad_size, tc2);
    if (foundToad1 || foundToad2) foundToad = true;
    */
}

void Board::checkSpaceShips()
{
    bool foundGlider1 = checkSpaceShip(gliders1, glider_size, glider_size, gc1, glider1Move);
    bool foundGlider2 = checkSpaceShip(gliders2, glider_size, glider_size, gc2, glider2Move);
    bool foundGlider3 = checkSpaceShip(gliders3, glider_size, glider_size, gc3, glider3Move);
    bool foundGlider4 = checkSpaceShip(gliders4, glider_size, glider_size, gc4, glider4Move);
    //if (foundGlider1 || foundGlider2 || foundGlider3 || foundGlider4) foundGlider = true;

    bool foundSc1 = checkSpaceShip(scs1, sc1_x_size, sc1_y_size, lwss1, sc1Move);
    bool foundSc2 = checkSpaceShip(scs2, sc2_x_size, sc2_y_size, lwss2, sc2Move);
    bool foundSc3 = checkSpaceShip(scs3, sc3_x_size, sc3_y_size, lwss3, sc3Move);
    bool foundSc4 = checkSpaceShip(scs4, sc4_x_size, sc4_y_size, lwss4, sc4Move);
    if (foundSc1 || foundSc2 || foundSc3 || foundSc4) foundLWSS = true;
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

bool Board::checkSpaceShip(const int* const patterns[4], int pattern_x_size, int pattern_y_size, SpaceShipCheck& sc, const pair<int, int> scMovement[4])
{

    if (sc.versionFound == -1) {
        for (int i = 0; i < 4; i++) {
            auto result = checkPattern(patterns[i], pattern_x_size, pattern_y_size);
            if (result.first) {
                sc.versionFound = i;
                sc.stepCount = 1;
                sc.x = result.second.first + scMovement[i].first;
                sc.y = result.second.second + scMovement[i].second;
                break;
            }
        }
    }
    else {
        int expectedPatternIndex = sc.versionFound + 1;
        if (expectedPatternIndex == 4) expectedPatternIndex = 0;
        auto result = checkPattern(patterns[expectedPatternIndex], pattern_x_size, pattern_y_size);
        if (result.first && result.second.first == sc.x && result.second.second == sc.y) {
            sc.versionFound = expectedPatternIndex;
            ++sc.stepCount;
            sc.x += scMovement[expectedPatternIndex].first;
            sc.y += scMovement[expectedPatternIndex].second;
            if (sc.stepCount == 4) {
                return true;
            }
        }
        else {
            sc.versionFound, sc.stepCount = 0;
            sc.x, sc.y = -1;
        }
    }
    return false;
}

pair<bool, pair<int, int>> Board::checkPattern(const int* pattern, int pattern_x_size, int pattern_y_size)
{
    bool foundPattern{ true };
    for (int i = 0; i <= x_size - pattern_x_size; i++) {
        for (int j = 0; j <= y_size - pattern_y_size; j++) {
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
                bool validSurroundings = true;
                for (int x = -1; x <= pattern_x_size; x++) {
                    for (int y = -1; y <= pattern_y_size; y++) {
                        int curX = i + x;
                        int curY = j + y;
                        if (x >= 0 && x < pattern_x_size && y >= 0 && y < pattern_y_size) {
                            continue;
                        }
                        if (curX < 0 || curX >= x_size || curY < 0 || curY >= y_size) {
                            continue;
                        }
                        int curIndex = getVectorIndex(curX, curY);
                        if (grid[curIndex] != 0) {
                            validSurroundings = false;
                            break;
                        }
                    }
                    if (!validSurroundings) break;
                }
                if (validSurroundings) {
                    return make_pair(true, make_pair(i, j));
                }
            }
        }
    }
    return make_pair(false, make_pair(-1, -1));
}