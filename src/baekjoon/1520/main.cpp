#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> myMap;
vector<vector<int>> dpTable;

int dpFunction(int x, int y) {
    if(dpTable[y][x] != -1) {
        return dpTable[y][x];
    }

    int result = 0;

    if(x - 1 >= 0 && myMap[y][x - 1] > myMap[y][x]) {
        result += dpFunction(x - 1, y);
    }

    if(x + 1 < myMap.front().size() && myMap[y][x + 1] > myMap[y][x]) {
        result += dpFunction(x + 1, y);
    }

    if(y - 1 >= 0 && myMap[y - 1][x] > myMap[y][x]) {
        result += dpFunction(x, y - 1);
    }

    if(y + 1 < myMap.size() && myMap[y + 1][x] > myMap[y][x]) {
        result += dpFunction(x, y + 1);
    }

    dpTable[y][x] = result;

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m = 0, n = 0;
    cin >> m >> n;

    myMap.assign(m, vector<int>(n, 0));
    dpTable.assign(m, vector<int>(n, -1));
    dpTable[0][0] = 1;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> myMap[i][j];
        }
    }

    cout << dpFunction(n - 1, m - 1);

    return 0;
}
