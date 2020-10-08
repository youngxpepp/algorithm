#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

int n = 0, m = 0;
vector<vector<int>> land;
vector<vector<int>> island;
vector<int> parents;
multimap<int, pair<int, int>> kruskalMap;

const vector<pair<int, int>> directions{{0,  -1},
                                        {0,  1},
                                        {-1, 0},
                                        {1,  0}};

void dfs(int num, pair<int, int> position) {
    island[position.second][position.first] = num;

    for (int i = 0; i < directions.size(); i++) {
        pair<int, int> nextPosition = position;
        nextPosition.first += directions[i].first;
        nextPosition.second += directions[i].second;

        if (nextPosition.first < 0 ||
            nextPosition.first >= m ||
            nextPosition.second < 0 ||
            nextPosition.second >= n) {
            continue;
        }

        if (land[nextPosition.second][nextPosition.first] == 0) {
            continue;
        }

        if (island[nextPosition.second][nextPosition.first] != -1) {
            continue;
        }

        dfs(num, nextPosition);
    }
}

int getParent(int num) {
    if (parents[num] == num) {
        return num;
    } else {
        return parents[num] = getParent(parents[num]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    land.assign(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> land[i][j];
        }
    }

    island.assign(n, vector<int>(m, -1));

    int islandCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (land[i][j] == 0 || island[i][j] != -1) {
                continue;
            }

            dfs(islandCount, {j, i});
            islandCount++;
        }
    }

    parents.assign(islandCount, 0);

    for (int i = 0; i < parents.size(); i++) {
        parents[i] = i;
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            cout << island[i][j] << "   ";
//        }
//        cout << endl;
//    }

    for (int i = 0; i < n; i++) {
        int islandNumber = island[i][0];
        int length = 0;
        for (int j = 0; j < m; j++) {
            if (island[i][j] == -1) {
                length++;
            } else if (islandNumber != -1 && island[i][j] != islandNumber) {
                kruskalMap.insert({length, {island[i][j], islandNumber}});
                length = 0;
                islandNumber = island[i][j];
            } else {
                islandNumber = island[i][j];
                length = 0;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int islandNumber = island[0][i];
        int length = 0;
        for (int j = 0; j < n; j++) {
            if (island[j][i] == -1) {
                length++;
            } else if (islandNumber != -1 && island[j][i] != islandNumber) {
                kruskalMap.insert({length, {island[j][i], islandNumber}});
                length = 0;
                islandNumber = island[j][i];
            } else {
                islandNumber = island[j][i];
                length = 0;
            }
        }
    }

    int answer = 0;

    for (auto itr = kruskalMap.begin(); itr != kruskalMap.end(); itr++) {
//        cout << itr->first << ", " << itr->second.first << " - " << itr->second.second << endl;

        if (itr->first < 2) {
            continue;
        }

        int aParent = getParent(itr->second.first);
        int bParent = getParent(itr->second.second);

        if (aParent < bParent) {
            parents[bParent] = aParent;
            answer += itr->first;
        } else if (bParent < aParent) {
            parents[aParent] = bParent;
            answer += itr->first;
        }
    }

    for (int i = 0; i < parents.size(); i++) {
        if (getParent(i) != getParent(0)) {
            cout << -1;
            return 0;
        }
    }

    cout << answer;

    return 0;
}
