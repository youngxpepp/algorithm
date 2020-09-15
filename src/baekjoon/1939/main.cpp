#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

bool bfs(int startNodeNumber, int endNodeNumber, int maxWeight, vector<vector<pair<int, int>>> &graph) {
    vector<bool> visit(graph.size(), false);
    visit[startNodeNumber] = true;

    queue<int> bfsQueue;
    bfsQueue.push(startNodeNumber);

    while(!bfsQueue.empty()) {
        int nodeNumber = bfsQueue.front();
        bfsQueue.pop();

        if(nodeNumber == endNodeNumber) {
            return true;
        }

        for(int i = 0; i < graph[nodeNumber].size(); i++) {
            int nextNodeNumber = graph[nodeNumber][i].first;
            int weight = graph[nodeNumber][i].second;

            if(weight < maxWeight) {
                continue;
            }

            if(visit[nextNodeNumber]) {
                continue;
            }

            visit[nextNodeNumber] = true;
            bfsQueue.push(nextNodeNumber);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());

    int minWeight = INT_MAX;
    int maxWeight = 0;

    for(int i = 0; i < m; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        graph[a - 1].emplace_back(b - 1, c);
        graph[b - 1].emplace_back(a - 1, c);
        minWeight = min(minWeight, c);
        maxWeight = max(maxWeight, c);
    }

    int d = 0, e = 0;
    cin >> d >> e;

    if(minWeight == maxWeight) {
        cout << minWeight;
        return 0;
    }

    int answer = 0;
    int left = minWeight;
    int right = maxWeight;

    while(left <= right) {
        int mid = (left + right) / 2;
        const bool bfsResult = bfs(d - 1, e - 1, mid, graph);

        if(bfsResult) {
            left = mid + 1;
            answer = max(answer, mid);
        } else {
            right = mid - 1;
        }
    }

    cout << answer;

    return 0;
}
