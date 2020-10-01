#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

int n = 0, e = 0, v1 = 0, v2 = 0;
vector<vector<pair<int, int>>> graph;

vector<int> dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(n, INT_MAX);

    pq.emplace(0, start);
    dist[start] = 0;

    while (!pq.empty()) {
        int nodeNumber = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (cost > dist[nodeNumber]) {
            continue;
        }

        for (int i = 0; i < graph[nodeNumber].size(); i++) {
            if (cost + graph[nodeNumber][i].second >= dist[graph[nodeNumber][i].first]) {
                continue;
            }

            dist[graph[nodeNumber][i].first] = cost + graph[nodeNumber][i].second;
            pq.emplace(dist[graph[nodeNumber][i].first], graph[nodeNumber][i].first);
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> e;

    graph.assign(n, vector<pair<int, int>>());

    for (int i = 0; i < e; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        a--;
        b--;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    cin >> v1 >> v2;
    v1--;
    v2--;

    vector<int> distV1 = dijkstra(v1);
    vector<int> distV2 = dijkstra(v2);
    vector<int> distDestination = dijkstra(n - 1);

    long long dist[]{(long long) distV1[0] + distV2[v1] + distDestination[v2],
                     (long long) distV2[0] + distV1[v2] + distDestination[v1]};

    if (dist[0] >= INT_MAX && dist[1] >= INT_MAX) {
        cout << -1;
    } else {
        cout << min(dist[0], dist[1]);
    }

    return 0;
}
