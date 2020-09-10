#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

vector<vector<int>> visit;
vector<vector<int>> table;
vector<int> paperCounts;

bool validate(pair<int, int> position, int paperNumber) {
    if(position.first + paperNumber >= 10) {
        return false;
    }

    if(position.second + paperNumber >= 10) {
        return false;
    }

    for(int i = position.second; i <= position.second + paperNumber; i++) {
        for(int j = position.first; j <= position.first + paperNumber; j++) {
            if(visit[i][j] == 1) {
                return false;
            }

            if(table[i][j] != 1) {
                return false;
            }
        }
    }

    return true;
}

void createPaperOnTable(pair<int, int> position, int paperNumber) {
    for(int i = position.second; i <= position.second + paperNumber; i++) {
        for(int j = position.first; j <= position.first + paperNumber; j++) {
            visit[i][j] = 1;
        }
    }
}

void deletePaperOnTable(pair<int, int> position, int paperNumber) {
    for(int i = position.second; i <= position.second + paperNumber; i++) {
        for(int j = position.first; j <= position.first + paperNumber; j++) {
            visit[i][j] = 0;
        }
    }
}

int dfs() {
    bool dfsExit = true;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(visit[i][j] != table[i][j]) {
                dfsExit = false;
            }
        }
    }

    if(dfsExit) {
        int result = 0;
        for(int i = 0; i < paperCounts.size(); i++) {
            result += paperCounts[i];
        }

        return result;
    }

    int value = -1;
    bool exit = false;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(table[i][j] != 1) {
                continue;
            }

            if(visit[i][j] == 1) {
                continue;
            }

            for(int k = 0; k < 5; k++) {
                if(paperCounts[k] >= 5) {
                    continue;
                }

                if(!validate(make_pair(j, i), k)) {
                    continue;
                }

                paperCounts[k]++;
                createPaperOnTable(make_pair(j, i), k);
                int dfsResult = dfs();

                if(dfsResult != -1) {
                    if(value == -1) {
                        value = dfsResult;
                    } else {
                        value = min(value, dfsResult);
                    }
                }

                paperCounts[k]--;
                deletePaperOnTable(make_pair(j, i), k);
            }
            exit = true;
            break;
        }
        if(exit) {
            break;
        }
    }

    return value;
}

int main() {
    table.assign(10, vector<int>(10, 0));
    visit.assign(10, vector<int>(10, 0));
    paperCounts.assign(5, 0);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> table[i][j];
        }
    }

    cout << dfs();

    return 0;
}
