#include <iostream>
#include <string>
#include <vector>

using namespace std;

int moveDownBlock(vector<vector<char>> &boardMap, vector<vector<bool>> &boardVisit) {
    int count = 0;

    for(int i = 0; i < boardMap.size() - 1; i++) {
        for (int j = 0; j < boardMap.front().size(); j++) {
            if(boardMap[i][j] == 0) {
                continue;
            }

            if(boardMap[i + 1][j] != 0) {
                continue;
            }

            boardMap[i + 1][j] = boardMap[i][j];
            boardMap[i][j] = 0;
            count++;
        }
    }

    return count;
}

int solution(int m, int n, vector<string> board) {
    vector<vector<char>> boardMap;
    vector<pair<int, int>> checkedPosition{{0, 0}, {1, 0}, {0, 1}, {1, 1}};

    for(auto &i : board) {
        boardMap.emplace_back();
        for(int j = 0; j < i.size(); j++) {
            boardMap.back().push_back(i[j]);
        }
    }

    int count = 0;
    int subCount = 0;
    do {
        subCount = 0;
        vector<vector<bool>> boardVisit(m, vector<bool>(n, false));

        for(int i = 0; i < m - 1; i++) {
            for(int j = 0; j < n - 1; j++) {
                bool allBlockSame = true;
                for(int k = 0; k < checkedPosition.size(); k++) {
                    int nx = j + checkedPosition[k].first;
                    int ny = i + checkedPosition[k].second;

                    if(boardMap[ny][nx] == 0 || boardMap[ny][nx] != boardMap[i][j]) {
                        allBlockSame = false;
                        break;
                    }
                }
                if(allBlockSame) {
                    for(int k = 0; k < checkedPosition.size(); k++) {
                        int nx = j + checkedPosition[k].first;
                        int ny = i + checkedPosition[k].second;

                        if(!boardVisit[ny][nx]) {
                            boardVisit[ny][nx] = true;
                            subCount++;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < boardMap.size(); i++) {
            for (int j = 0; j < boardMap.front().size(); j++) {
                if(boardVisit[i][j]) {
                    boardMap[i][j] = 0;
                }
            }
        }

        while(moveDownBlock(boardMap, boardVisit) != 0);

        count += subCount;
    } while(subCount != 0);

    return count;
}
