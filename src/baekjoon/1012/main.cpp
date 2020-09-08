#include <iostream>
#include <vector>

using namespace std;

const vector<pair<int, int>> directions{{0 ,-1}, {0 ,1}, {-1, 0}, {1, 0}};

void dfs(int landNumber, pair<int, int> position, vector<vector<int>> &land, vector<vector<int>> &visit) {
    visit[position.second][position.first] = landNumber;

    for(int i = 0; i < directions.size(); i++) {
        int nx = position.first + directions[i].first;
        int ny = position.second + directions[i].second;

        if(nx < 0 || nx >= land.front().size() || ny < 0 || ny >= land.size()) {
            continue;
        }

        if(visit[ny][nx] != -1) {
            continue;
        }

        if(land[ny][nx] != 1) {
            continue;
        }

        dfs(landNumber, make_pair(nx, ny), land, visit);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 0;

    cin >> t;

    for(int i = 0; i < t; i++) {
        int m = 0, n = 0, k = 0;
        cin >> m >> n >> k;

        vector<vector<int>> land(n, vector<int>(m, 0));

        for(int j = 0; j < k; j++) {
            int x = 0, y = 0;
            cin >> x >> y;
            land[y][x] = 1;
        }

        int landNumber = 0;
        vector<vector<int>> visit(n, vector<int>(m, -1));

        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                if(visit[j][k] != -1) {
                    continue;
                }

                if(land[j][k] != 1) {
                    continue;
                }

                dfs(landNumber++, make_pair(k, j), land, visit);
            }
        }

        cout << landNumber << "\n";
    }

    return 0;
}
