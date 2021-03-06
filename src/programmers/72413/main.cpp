#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <functional>

using namespace std;

int dijkstra(int src, int dest, const vector<vector<int>> &graph);
vector<long long> dijkstras(int src, const vector<vector<int>> &graph);

int dijkstra(int src, int dest, const vector<vector<int>> &graph) {
    return dijkstras(src, graph)[dest];
}

vector<long long> dijkstras(int src, const vector<vector<int>> &graph) {
    vector<long long> distances(graph.size(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distances[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        if (top.first > distances[top.second]) {
            continue;
        }

        for (int i = 0; i < graph[top.second].size(); i++) {
            if (graph[top.second][i] == -1) {
                continue;
            }

            long long dist = top.first + graph[top.second][i];
            if (dist >= distances[i]) {
                continue;
            }

            distances[i] = dist;
            pq.push({dist, i});
        }
    }

    return distances;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    long long answer = 0;

    vector<vector<int>> graph(n, vector<int>(n, -1));

    for (int i = 0; i < fares.size(); i++) {
        int c = fares[i][0] - 1;
        int d = fares[i][1] - 1;
        int f = fares[i][2];

        graph[c][d] = f;
        graph[d][c] = f;
    }

    vector<long long> a_costs = dijkstras(a - 1, graph);
    vector<long long> b_costs = dijkstras(b - 1, graph);
    vector<long long> s_costs = dijkstras(s - 1, graph);

    answer = s_costs[a - 1] + s_costs[b - 1];

    for (int i = 0; i < n; i++) {
        if (i == s - 1) {
            continue;
        }
        long long cost = a_costs[i] + b_costs[i] + s_costs[i];
        if (cost < answer) {
            answer = cost;
        }
    }

    return (int)answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}
