#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <functional>
#include <algorithm>

using namespace std;

long long n = 0, m = 0;
vector<long long> oilPrices;
vector<vector<pair<long long, long long>>> graph;

long long dijkstra(long long start) {
    vector<vector<bool>> visit(n, vector<bool>(2501, false));
    priority_queue<tuple<long long, long long, long long>, vector<tuple<long long, long long, long long>>, greater<>> pq;

    pq.emplace(make_tuple(0, start, oilPrices[start]));

    while (!pq.empty()) {
        long long cost = get<0>(pq.top());
        long long nodeNumber = get<1>(pq.top());
        long long minOilPrice = get<2>(pq.top());
        pq.pop();

        if (visit[nodeNumber][minOilPrice]) {
            continue;
        }

        if (nodeNumber == n - 1) {
            return cost;
        }

        visit[nodeNumber][minOilPrice] = true;

        for (long long i = 0; i < graph[nodeNumber].size(); i++) {
            long long nextNodeNumber = graph[nodeNumber][i].first;
            long long nextCost = cost + graph[nodeNumber][i].second * minOilPrice;
            long long nextMinOilPrice = min(minOilPrice, oilPrices[nextNodeNumber]);

            pq.emplace(nextCost, nextNodeNumber, nextMinOilPrice);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    oilPrices.assign(n, 0);
    graph.assign(n, vector<pair<long long, long long>>());

    for (auto &oilPrice : oilPrices) {
        cin >> oilPrice;
    }

    for (long long i = 0; i < m; i++) {
        long long a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        a--;
        b--;

        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    cout << dijkstra(0);

    return 0;
}
