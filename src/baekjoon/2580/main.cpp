#include <iostream>
#include <vector>

using namespace std;

bool finished = false;
vector<vector<bool>> row(9, vector<bool>(10, false));
vector<vector<bool>> column(9, vector<bool>(10, false));
vector<vector<bool>> threeByThree(9, vector<bool>(10, false));

void dfs(int depth, vector<pair<int, int>> &emptyArr, vector<vector<int>> &sdoku);
int getSquareNumber(int x, int y);

void dfs(int depth, vector<pair<int, int>> &emptyArr, vector<vector<int>> &sdoku) {
    if(finished) {
        return;
    }

    if(depth == emptyArr.size()) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                cout << sdoku[i][j] << " ";
            }
            cout << "\n";
        }
        finished = true;
    }

    int x = emptyArr[depth].first;
    int y = emptyArr[depth].second;
    int squareNumber = getSquareNumber(x, y);

    for(int i = 1; i <= 9; i++) {
        if(row[y][i] || column[x][i] || threeByThree[squareNumber][i]) {
            continue;
        }

        sdoku[y][x] = i;

        row[y][i] = true;
        column[x][i] = true;
        threeByThree[squareNumber][i] = true;

        dfs(depth + 1, emptyArr, sdoku);

        row[y][i] = false;
        column[x][i] = false;
        threeByThree[squareNumber][i] = false;
    }
}

int getSquareNumber(int x, int y) {
    int nx = (x / 3) * 3;
    int ny = (y / 3) * 3;

    return (nx + ny) / 3 + 2 * (ny / 3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> sdoku(9, vector<int>(9, 0));
    vector<pair<int, int>> emptyArr;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin >> sdoku[i][j];

            if(sdoku[i][j] == 0) {
                emptyArr.emplace_back(j, i);
            } else {
                row[i][sdoku[i][j]] = true;
                column[j][sdoku[i][j]] = true;
                threeByThree[getSquareNumber(j, i)][sdoku[i][j]] = true;
            }
        }
    }

    dfs(0, emptyArr, sdoku);

    return 0;
}
