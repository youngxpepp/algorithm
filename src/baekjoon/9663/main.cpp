#include <iostream>
#include <vector>

using namespace std;

vector<bool> rows;
vector<bool> columns;
vector<bool> crossLineOne;
vector<bool> crossLineTwo;

int dfs(int depth, vector<vector<int>> &plate) {
    if(depth == plate.size()) {
        return 1;
    }

    int value = 0;

    for(int i = 0; i < plate.size(); i++) {
        int crossLineOneIndex = (i - depth) + (plate.size() - 1);
        int crossLineTwoIndex = i + depth;

        if(rows[i] || columns[depth] || crossLineOne[crossLineOneIndex] || crossLineTwo[crossLineTwoIndex]) {
            continue;
        }

        rows[i] = true;
        columns[depth]  = true;
        crossLineOne[crossLineOneIndex] = true;
        crossLineTwo[crossLineTwoIndex] = true;

        value += dfs(depth + 1, plate);

        rows[i] = false;
        columns[depth]  = false;
        crossLineOne[crossLineOneIndex] = false;
        crossLineTwo[crossLineTwoIndex] = false;
    }

    return value;
}

int main() {
    int n = 0;
    cin >> n;

    vector<vector<int>> plate(n, vector<int>(n, 0));

    rows.assign(n, false);
    columns.assign(n, false);
    crossLineOne.assign((2 * n) - 1, false);
    crossLineTwo.assign((2 * n) - 1, false);

    cout << dfs(0, plate);

    return 0;
}
