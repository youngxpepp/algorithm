#include <iostream>
#include <vector>
#include <queue>
#define MAX_DEPTH 40000
#define MAX_HOP 15

using namespace std;

int n = 0, m = 0;
vector<int> depthVector;
vector<vector<int>> dists;
vector<vector<int>> parents;
vector<vector<pair<int, int>>> graph;

void bfs(int start) {
    vector<bool> visit(n, false);
    queue<pair<int, int>> q;

    visit[start] = true;
    q.emplace(start, 0);

    while (!q.empty()) {
        int nodeNumber = q.front().first;
        int depth = q.front().second;
        q.pop();

        depthVector[nodeNumber] = depth;

        for (int i = 0; i < graph[nodeNumber].size(); i++) {
            int nextNodeNumber = graph[nodeNumber][i].first;
            int distance = graph[nodeNumber][i].second;

            if (visit[nextNodeNumber]) {
                continue;
            }

            visit[nextNodeNumber] = true;
            parents[nextNodeNumber][0] = nodeNumber;
            dists[nextNodeNumber][0] = distance;
            q.emplace(nextNodeNumber, depth + 1);
        }
    }
}

int getDistanceFromRoot(const int node) {
    int now = node;
    int dist = 0;
    for (int i = MAX_HOP; i >= 0; i--) {
        if (depthVector[now] >= (1 << i)) {
            dist += dists[now][i];
            now = parents[now][i];
        }
    }
    return dist;
}

int lca(const int x, const int y) {
    if (x == y) {
        return x;
    }

    int deep = x, shallow = y;

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
        if (parents[deep][i] == -1 || parents[shallow][i] == -1) {
            continue;
        }

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

    graph.assign(n, vector<pair<int, int>>());

    for (int i = 0; i < n - 1; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        a--;
        b--;

        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    depthVector.assign(n, 0);
    parents.assign(n, vector<int>(MAX_HOP + 1, -1));
    dists.assign(n, vector<int>(MAX_HOP + 1, 0));

    bfs(0);

    for (int i = 1; i <= MAX_HOP; i++) {
        for (int j = 1; j < n; j++) {
            if (depthVector[j] < (1 << i)) {
                continue;
            }

            parents[j][i] = parents[parents[j][i - 1]][i - 1];
            dists[j][i] = dists[j][i - 1] + dists[parents[j][i - 1]][i - 1];
        }
    }

    cin >> m;

    for (int j = 0; j < m; j++) {
        int x = 0, y = 0;
        cin >> x >> y;
        x--;
        y--;

        if (x == y) {
            cout << 0 << '\n';
            continue;
        }

        int commonParent = lca(x, y);

        int xd = getDistanceFromRoot(x);
        int yd = getDistanceFromRoot(y);
        int cd = getDistanceFromRoot(commonParent);

        cout << (xd + yd) - 2 * cd << '\n';
    }

    return 0;
}
