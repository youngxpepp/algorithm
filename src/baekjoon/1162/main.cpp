#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#include <algorithm>

using namespace std;

int n = 0, m = 0, k = 0;
vector<vector<pair<int, int>>> graph;

long long dijkstra(int start) {
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
    vector<vector<long long>> dists(n, vector<long long>(k + 1, LONG_LONG_MAX));

    pq.emplace(0, 0, 0);
    for (int i = 0; i < dists[0].size(); i++) {
        dists[0][i] = 0;
    }

    while (!pq.empty()) {
        long long dist = get<0>(pq.top());
        int nodeNum = get<1>(pq.top());
        int roads = get<2>(pq.top());
        pq.pop();

        if (dist > dists[nodeNum][roads]) {
            continue;
        }

        for (int i = 0; i < graph[nodeNum].size(); i++) {
            int nextNodeNum = graph[nodeNum][i].first;
            long long nextDist = dist + graph[nodeNum][i].second;
            int nextRoads = roads;

            if (nextDist < dists[nextNodeNum][nextRoads]) {
                dists[nextNodeNum][nextRoads] = nextDist;
                pq.emplace(nextDist, nextNodeNum, nextRoads);
            }

            if (nextRoads + 1 <= k && nextDist - graph[nodeNum][i].second < dists[nextNodeNum][nextRoads + 1]) {
                dists[nextNodeNum][nextRoads + 1] = nextDist - graph[nodeNum][i].second;
                pq.emplace(nextDist - graph[nodeNum][i].second, nextNodeNum, nextRoads + 1);
            }
        }
    }

    vector<long long> resultDist = dists[n - 1];
    sort(resultDist.begin(), resultDist.end());

    return resultDist[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    graph.assign(n, vector<pair<int, int>>());

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        a--;
        b--;

        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    cout << dijkstra(0);

    return 0;
}
