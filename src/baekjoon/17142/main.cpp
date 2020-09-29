#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int minDepth = INT_MAX;
vector<vector<int>> table;
vector<pair<int, int>> emptySpaces;
vector<pair<int, int>> viruses;
vector<vector<pair<int, int>>> virusCombinations;
vector<pair<int, int>> directions{{0,  -1},
                                  {0,  1},
                                  {-1, 0},
                                  {1,  0}};

void dfsCombination(int index, int m, vector<int> combination) {
    if (combination.size() == m) {
        virusCombinations.emplace_back();
        for (int i = 0; i < combination.size(); i++) {
            virusCombinations.back().push_back(viruses[combination[i]]);
        }

        return;
    }

    for (int i = index; i < viruses.size(); i++) {
        combination.push_back(i);
        dfsCombination(i + 1, m, combination);
        combination.pop_back();
    }
}

int bfs(vector<pair<int, int>> &combination) {
    vector<vector<bool>> visit(table.size(), vector<bool>(table.size(), false));
    vector<vector<bool>> infected(table.size(), vector<bool>(table.size(), false));
    queue<pair<int, pair<int, int>>> bfsQueue;

    for (int i = 0; i < combination.size(); i++) {
        bfsQueue.emplace(0, combination[i]);
        visit[combination[i].second][combination[i].first] = true;
    }


    while (!bfsQueue.empty()) {
        int depth = bfsQueue.front().first;
        pair<int, int> virus = bfsQueue.front().second;
        bfsQueue.pop();

        infected[virus.second][virus.first] = true;

        if (depth >= minDepth) {
            return -1;
        }

        bool correct = true;
        for (int i = 0; i < emptySpaces.size(); i++) {
            if (!infected[emptySpaces[i].second][emptySpaces[i].first]) {
                correct = false;
                break;
            }
        }

        if (correct) {
            return depth;
        }

        for (int i = 0; i < directions.size(); i++) {
            pair<int, int> nextVirus = virus;
            nextVirus.first += directions[i].first;
            nextVirus.second += directions[i].second;

            if (nextVirus.first < 0 || nextVirus.first >= table.size() || nextVirus.second < 0 ||
                nextVirus.second >= table.size()) {
                continue;
            }

            if (visit[nextVirus.second][nextVirus.first]) {
                continue;
            }

            if (table[nextVirus.second][nextVirus.first] == 1) {
                continue;
            }

            visit[nextVirus.second][nextVirus.first] = true;
            bfsQueue.emplace(depth + 1, nextVirus);
        }
    }


    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;
    table.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> table[i][j];

            if (table[i][j] == 2) {
                viruses.emplace_back(j, i);
            }

            if (table[i][j] == 0) {
                emptySpaces.emplace_back(j, i);
            }
        }
    }

    dfsCombination(0, m, vector<int>());

    for (int i = 0; i < virusCombinations.size(); i++) {
        int result = bfs(virusCombinations[i]);

        if (result != -1) {
            minDepth = min(minDepth, result);
        }
    }

    if (minDepth == INT_MAX) {
        cout << -1;
    } else {
        cout << minDepth;
    }


    return 0;
}
