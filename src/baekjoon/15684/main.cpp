#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<bool>> ladders;

bool isLadderCorrect() {
    for(int i = 0; i < ladders.size(); i++) {
        int ladderNumber = i;
        for(int j = 0; j < ladders.front().size(); j++) {
            if(ladderNumber > 0 && ladders[ladderNumber - 1][j]) {
                ladderNumber--;
            } else if(ladderNumber < ladders.size() - 1 && ladders[ladderNumber][j]) {
                ladderNumber++;
            }
        }

        if(ladderNumber != i) {
            return false;
        }
    }

    return true;
}

int dfs(int depth, int ladderNumber, int verticalNumber) {
    if(isLadderCorrect()) {
        return depth;
    }

    if(depth >= 3) {
        return -1;
    }

    int result = -1;

    for(int i = ladderNumber; i < ladders.size() - 1; i++) {
        for(int j = 0; j < ladders.front().size(); j++) {
            if(i == ladderNumber && j <= verticalNumber) {
                continue;
            }

            if(ladders[i][j]) {
                continue;
            }

            if(i > 0 && ladders[i - 1][j]) {
                continue;
            }
            if(ladders[i + 1][j]) {
                continue;
            }

            ladders[i][j] = true;
            int dfsResult = dfs(depth + 1, i, j);
            ladders[i][j] = false;

            if(dfsResult != -1) {
                if(result == -1) {
                    result = dfsResult;
                } else {
                    result = min(result, dfsResult);
                }
            }
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0, h = 0;
    cin >> n >> m >> h;

    ladders.assign(n, vector<bool>(h, false));

    for(int i = 0; i < m; i++) {
        int a = 0, b = 0;
        cin >> a >> b;

        ladders[b - 1][a - 1] = true;
    }

    cout << dfs(0, 0, -1);

    return 0;
}
