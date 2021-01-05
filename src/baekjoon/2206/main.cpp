#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int n = 0, m = 0;
int matrix[1000][1000] = {0,};
const pair<int, int> directions[] = {{1,  0},
                                     {-1, 0},
                                     {0,  1},
                                     {0,  -1}};

class bfs_node {
public:
    pair<int, int> position;
    int distance;
    int wall_count;

    bfs_node(pair<int, int> position, int distance = 1, int wall_count = 0) : position(position), distance(distance),
                                                                              wall_count(wall_count) {}
};

int bfs(pair<int, int> start) {
    vector<vector<vector<int>>> visit(1000, vector<vector<int>>(1000, vector<int>(2, -1)));;
    visit[start.second][start.first][0] = 1;
    queue<bfs_node> q;
    q.push(bfs_node(start));

    while (!q.empty()) {
        bfs_node node = q.front();
        q.pop();

        if (node.position.first == m - 1 && node.position.second == n - 1) {
            return node.distance;
        }

        for (int i = 0; i < 4; i++) {
            pair<int, int> next_position = node.position;
            next_position.first += directions[i].first;
            next_position.second += directions[i].second;
            int next_distance = node.distance + 1;
            int next_wall_count = node.wall_count;

            if (next_position.first < 0 ||
                next_position.first >= m ||
                next_position.second < 0 ||
                next_position.second >= n) {
                continue;
            }

            if (matrix[next_position.second][next_position.first] == 1) {
                if (node.wall_count == 1) {
                    continue;
                }
                next_wall_count++;
            }

            if (visit[next_position.second][next_position.first][node.wall_count] != -1 &&
                next_distance >= visit[next_position.second][next_position.first][node.wall_count]) {
                continue;
            }

            visit[next_position.second][next_position.first][node.wall_count] = next_distance;
            q.push(bfs_node(next_position, next_distance, next_wall_count));
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string input = "";
        cin >> input;
        for (int j = 0; j < input.size(); j++) {
            if (input[j] == '1') {
                matrix[i][j] = 1;
            } else if (input[j] == '0') {
                matrix[i][j] = 0;
            }
        }
    }

    cout << bfs({0, 0}) << '\n';

    return 0;
}
