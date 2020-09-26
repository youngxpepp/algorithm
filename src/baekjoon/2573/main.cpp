#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> directions = {{0,  -1},
                                     {0,  1},
                                     {-1, 0},
                                     {1,  0}};

void dfs(pair<int, int> position, int visitNumber, vector<vector<int>> &visit, vector<vector<int>> &icebergs) {
    for (int i = 0; i < directions.size(); i++) {
        pair<int, int> nPosition(position.first + directions[i].first, position.second + directions[i].second);

        if (nPosition.first < 0 || nPosition.first >= icebergs.front().size() || nPosition.second < 0 ||
            nPosition.second >= icebergs.size()) {
            continue;
        }

        if (icebergs[nPosition.second][nPosition.first] == 0) {
            continue;
        }

        if (visit[nPosition.second][nPosition.first] != -1) {
            continue;
        }

        visit[nPosition.second][nPosition.first] = visitNumber;
        dfs(nPosition, visitNumber, visit, icebergs);
    }
}

int getHowManyIcebergLumps(vector<vector<int>> &icebergs) {
    vector<vector<int>> visit(icebergs.size(), vector<int>(icebergs.front().size(), -1));
    int visitNumber = 0;

    for (int i = 0; i < icebergs.size(); i++) {
        for (int j = 0; j < icebergs.front().size(); j++) {
            if (visit[i][j] != -1) {
                continue;;
            }

            if (icebergs[i][j] == 0) {
                continue;
            }

            dfs({j, i}, visitNumber++, visit, icebergs);
        }
    }

    return visitNumber;
}

void melt(vector<vector<int>> &icebergs) {
    vector<vector<int>> copied = icebergs;

    for (int i = 0; i < icebergs.size(); i++) {
        for (int j = 0; j < icebergs.front().size(); j++) {
            if (icebergs[i][j] == 0) {
                continue;
            }

            int nearbyIcebergCount = 0;
            for (int k = 0; k < directions.size(); k++) {
                pair<int, int> position(j + directions[k].first, i + directions[k].second);

                if (position.first < 0 || position.first >= icebergs.front().size() || position.second < 0 ||
                    position.second >= icebergs.size()) {
                    continue;
                }

                if (copied[position.second][position.first] == 0) {
                    nearbyIcebergCount++;
                }
            }

            icebergs[i][j] -= nearbyIcebergCount;
            if (icebergs[i][j] < 0) {
                icebergs[i][j] = 0;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;
    vector<vector<int>> icebergs(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> icebergs[i][j];
        }
    }

    int years = 0;
    int icebergLumpCount = getHowManyIcebergLumps(icebergs);

    if(icebergLumpCount == 0) {
        cout << 0;
        return 0;
    }

    while (icebergLumpCount < 2) {
        melt(icebergs);
        icebergLumpCount = getHowManyIcebergLumps(icebergs);
        years++;

        if(icebergLumpCount == 0) {
            cout << 0;
            return 0;
        }
    }

    cout << years;

    return 0;
}
