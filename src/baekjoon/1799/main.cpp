#include <iostream>
#include <vector>

using namespace std;

int n = 0;
vector<pair<int, int>> chessHorsesOnBlack;
vector<pair<int, int>> chessHorsesOnWhite;
vector<vector<bool>> crossLine;

int dfs(int depth, int chessHorseIndex, vector<pair<int, int>> &chessHorses) {
    int value = 0;

    for(int i = chessHorseIndex; i < chessHorses.size(); i++) {
        int x = chessHorses[i].first;
        int y = chessHorses[i].second;

        vector<int> crossLineIndices{x + y, (int)(y - x + n - 1)};

        if(crossLine[0][crossLineIndices[0]]) {
            continue;
        }

        if(crossLine[1][crossLineIndices[1]]) {
            continue;
        }

        crossLine[0][crossLineIndices[0]] = true;
        crossLine[1][crossLineIndices[1]] = true;

        value = max(value, dfs(depth + 1, i + 1, chessHorses));

        crossLine[0][crossLineIndices[0]] = false;
        crossLine[1][crossLineIndices[1]] = false;
    }

    if(value == 0) {
        return depth;
    }

    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    crossLine.assign(2, vector<bool>(2 * n - 1, false));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int input = 0;
            cin >> input;

            if(input == 1) {
                if((i + j) % 2 == 0) {
                    chessHorsesOnBlack.emplace_back(j, i);
                } else {
                    chessHorsesOnWhite.emplace_back(j, i);
                }
            }
        }
    }

    cout << dfs(0, 0, chessHorsesOnBlack) + dfs(0, 0, chessHorsesOnWhite);

    return 0;
}
