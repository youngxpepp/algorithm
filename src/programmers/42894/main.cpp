#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<int>> globalBoard;
vector<vector<pair<int, int>>> checkedBlockPosition{
    {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}},
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}},
    {{0, 0}, {-1, 0}, {0, 1}, {-1, 1}, {0, 2}, {-1, 2}},
    {{0, 0}, {-1, 0}, {-2, 0}, {0, 1}, {-1, 1}, {-2, 1}},
    {{0, 0}, {-1, 0}, {-2, 0}, {0, -1}, {-1, -1}, {-2, -1}},
    {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}, {0, -2}, {-1, -2}},
    {{0, 0}, {1, 0}, {0, -1}, {1, -1}, {0, -2}, {1, -2}},
    {{0, 0}, {1, 0}, {2, 0}, {0, -1}, {1, -1}, {2, -1}}};

int checkRectangle(int x, int y) {
    for(int i = 0; i < 8; i++) {
        int color = 0;
        unordered_map<int ,int> colorCountMap;

        for(int j = 0; j < 6; j++) {
            int nextX = x + checkedBlockPosition[i][j].first;
            int nextY = y + checkedBlockPosition[i][j].second;

            if(nextX < 0 || nextX >= globalBoard.size() || nextY < 0 || nextY >= globalBoard.size()) {
                break;
            }

            if(globalBoard[nextY][nextX] == 0) {
                break;
            }

            if(globalBoard[nextY][nextX] > 0) {
                color = globalBoard[nextY][nextX];
            }

            colorCountMap[globalBoard[nextY][nextX]]++;
        }

        if(colorCountMap[-1] == 2 && color > 0 && colorCountMap[color] == 4) {
            return i;
        }
    }

    return -1;
}

int solution(vector<vector<int>> board) {
    globalBoard = board;

    int answer = 0;

    for(int i = 0; i < globalBoard.size(); i++) {
        for(int j = 0; j < globalBoard.size(); j++) {
            if(globalBoard[i][j] == 0) {
                bool upBlock = false;
                for(int k = i - 1; k >= 0; k--) {
                    if(globalBoard[k][j] > 0) {
                        upBlock = true;
                        break;
                    }
                }

                if(!upBlock) {
                    globalBoard[i][j] = -1;
                }
            }
            else if(globalBoard[i][j] > 0) {
                int checkedBlockPositionIndex = checkRectangle(j, i);
                if(checkedBlockPositionIndex != - 1) {
                    answer++;

                    for(int k = 0; k < 6; k++) {
                        int x = j + checkedBlockPosition[checkedBlockPositionIndex][k].first;
                        int y = i + checkedBlockPosition[checkedBlockPositionIndex][k].second;

                        globalBoard[y][x] = 0;
                    }

                    for(int k = 0; k < 6; k++) {
                        int x = j + checkedBlockPosition[checkedBlockPositionIndex][k].first;
                        int y = i + checkedBlockPosition[checkedBlockPositionIndex][k].second;

                        bool upBlock = false;
                        for(int l = y - 1; l >= 0; l--) {
                            if(globalBoard[l][x] > 0) {
                                upBlock = true;
                                break;
                            }
                        }

                        if(!upBlock) {
                            globalBoard[y][x] = -1;
                        }
                    }
                }
            }
        }
    }

    return answer;
}