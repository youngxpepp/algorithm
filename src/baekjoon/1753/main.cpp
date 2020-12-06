#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> graph;

vector<int> dijkstra(int start_vertex, int vertex_size) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> distances(vertex_size, INT_MAX);

    pq.push({0, start_vertex});
    distances[start_vertex] = 0;

    while (!pq.empty()) {
        int distance = pq.top().first;
        int vertex = pq.top().second;
        pq.pop();

        if (distance > distances[vertex]) {
            continue;
        }

        for (int i = 0; i < graph[vertex].size(); i++) {
            int next_vertex = graph[vertex][i].first;
            int next_distance = distance + graph[vertex][i].second;

            if (next_distance < distances[next_vertex]) {
                pq.push({next_distance, next_vertex});
                distances[next_vertex] = next_distance;
            }
        }
    }

    return distances;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int v = 0, e = 0, k = 0;

    cin >> v >> e >> k;
    graph.assign(v, vector<pair<int, int>>());

    for (int i = 0; i < e; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        graph[a - 1].push_back({b - 1, c});
    }

    vector<int> answer = dijkstra(k - 1, v);

    for (int i = 0; i < answer.size(); i++) {
        if (answer[i] == INT_MAX) {
            cout << "INF" << "\n";
        } else {
            cout << answer[i] << "\n";
        }
    }

    return 0;
}
