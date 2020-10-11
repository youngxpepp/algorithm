#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define MAX_HOP 21

using namespace std;

int n = 0, m = 0;
vector<vector<int>> graph;
vector<int> depthVector;
vector<vector<int>> parents;

void bfs(int start) {
    vector<bool> visit(n, false);
    queue<pair<int, int>> q;
    q.push({start, 0});
    visit[start] = true;

    while (!q.empty()) {
        int nodeNumber = q.front().first;
        int depth = q.front().second;
        q.pop();

        depthVector[nodeNumber] = depth;

        for (int i = 0; i < graph[nodeNumber].size(); i++) {
            if (visit[graph[nodeNumber][i]]) {
                continue;
            }

            visit[graph[nodeNumber][i]] = true;
            parents[graph[nodeNumber][i]][0] = nodeNumber;
            q.emplace(graph[nodeNumber][i], depth + 1);
        }
    }
}

int lca(const int x, const int y) {
    int bigger = x;
    int smaller = y;

    if (depthVector[bigger] < depthVector[smaller]) {
        swap(bigger, smaller);
    }

    for (int i = MAX_HOP; i >= 0; i--) {
        if (depthVector[bigger] - depthVector[smaller] >= (1 << i)) {
            bigger = parents[bigger][i];
        }
    }

    if (bigger == smaller) {
        return smaller;
    }

    for (int i = MAX_HOP; i >= 0; i--) {
        if (parents[bigger][i] != parents[smaller][i]) {
            bigger = parents[bigger][i];
            smaller = parents[smaller][i];
        }
    }

    return parents[bigger][0];
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
        for (int j = 0; j < n; j++) {
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
