#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> table;
vector<vector<long long>> dpTable;

long long dpFunction(int x, int y) {
    if(dpTable[y][x] != -1) {
        return dpTable[y][x];
    }

    long long result = 0;
    int nx = x - 1;
    int ny = y - 1;

    while(nx >= 0) {
        int diff = x - nx;
        if(table[y][nx] != diff) {
            nx--;
            continue;
        }
        result += dpFunction(nx, y);
        nx--;
    }

    while(ny >= 0) {
        int diff = y - ny;
        if(table[ny][x] != diff) {
            ny--;
            continue;
        }
        result += dpFunction(x, ny);
        ny--;
    }

    dpTable[y][x] = result;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    table.assign(n, vector<int>(n, 0));
    dpTable.assign(n, vector<long long>(n, -1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> table[i][j];
        }
    }

    dpTable[0][0] = 1;

    cout << dpFunction(n - 1, n - 1);

    return 0;
}
