#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(vector<vector<int>> &graph) {
    vector<int> visit(graph.size(), 0);

    for(int i = 0; i < graph.size(); i++) {
        if(visit[i] != 0) {
            continue;
        }

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(i, 1);
        while(!bfsQueue.empty()) {
            int num = bfsQueue.front().first;
            int color = bfsQueue.front().second;
            bfsQueue.pop();

            for(int j = 0; j < graph[num].size(); j++) {
                if(visit[graph[num][j]] == color) {
                    return false;
                } else if(visit[graph[num][j]] == -color) {
                    continue;
                }

                visit[graph[num][j]] = -color;
                bfsQueue.emplace(graph[num][j], -color);
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 0;
    cin >> t;

    for(int i = 0; i < t; i++) {
        int v = 0, e = 0;
        cin >> v >> e;

        vector<vector<int>> graph(v, vector<int>());

        for(int j = 0; j < e; j++) {
            int a = 0, b = 0;
            cin >> a >> b;
            graph[a - 1].push_back(b - 1);
            graph[b - 1].push_back(a - 1);
        }

        if(bfs(graph)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
