#include <iostream>
#include <vector>
#include <queue>
#define MAX_HOP 15

using namespace std;

int n = 0, m = 0;
vector<vector<int>> graph;
vector<int> depthVector;
vector<vector<int>> parents;

void bfs(int start) {
    queue<pair<int, int>> q;
    vector<bool> visit(n, false);

    q.push({start, 0});
    visit[start] = true;

    while (!q.empty()) {
        int nodeNumber = q.front().first;
        int depth = q.front().second;
        q.pop();

        depthVector[nodeNumber] = depth;

        for (int i = 0; i < graph[nodeNumber].size(); i++) {
            int nextNodeNumber = graph[nodeNumber][i];

            if (visit[nextNodeNumber]) {
                continue;
            }

            parents[nextNodeNumber][0] = nodeNumber;
            visit[nextNodeNumber] = true;
            q.push({nextNodeNumber, depth + 1});
        }
    }
}

int lca(const int x, const int y) {
    int deep = x;
    int shallow = y;

    if (depthVector[deep] < depthVector[shallow]) {
        swap(deep, shallow);
    }

    for (int i = MAX_HOP; i >= 0; i--) {
        if (depthVector[deep] - depthVector[shallow] >= (1 << i)) {
            deep = parents[deep][i];
        }
    }

    if (deep == shallow) {
        return deep;
    }

    for (int i = MAX_HOP; i >= 0; i--) {
        if (parents[deep][i] != parents[shallow][i]) {
            deep = parents[deep][i];
            shallow = parents[shallow][i];
        }
    }

    return parents[deep][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    graph.assign(n, vector<int>());
    depthVector.assign(n, 0);
    parents.assign(n, vector<int>(MAX_HOP, 0));

    for (int i = 0; i < n - 1; i++) {
        int a = 0, b = 0;
        cin >> a >> b;
        a--;
        b--;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs(0);

    for (int i = 1; i <= MAX_HOP; i++) {
        for (int j = 1; j < n; j++) {
            parents[j][i] = parents[parents[j][i - 1]][i - 1];
        }
    }

    cin >> m;

    for (int i = 0; i < m; i++) {
        int x = 0, y = 0;
        cin >> x >> y;
        x--;
        y--;

        cout << lca(x, y) + 1 << '\n';
    }


    return 0;
}
