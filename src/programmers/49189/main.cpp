#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>

using namespace std;

vector<vector<bool>> graph;
vector<int> distances;

int bfs(int n) {
    int longestDistance = 0;
    queue<pair<int, int>> bfsQueue;
    vector<bool> visit(n, false);
    bfsQueue.push(make_pair(0, 0));
    visit[0] = true;

    while(!bfsQueue.empty()) {
        int nodeNumber = bfsQueue.front().first;
        int distance = bfsQueue.front().second;
        bfsQueue.pop();

        longestDistance = max(longestDistance, distance);
        distances[nodeNumber] = max(distances[nodeNumber], distance);

        for(int i = 0; i < graph[nodeNumber].size(); i++) {
            if(!graph[nodeNumber][i]) {
                continue;
            }

            if(visit[i]) {
                continue;
            }

            visit[i] = true;
            bfsQueue.push(make_pair(i, distance + 1));
        }
    }

    return longestDistance;
}

int solution(int n, vector<vector<int>> edge) {
    graph.assign(n, vector<bool>(n, false));
    distances.assign(n, 0);

    for(const auto e : edge) {
        graph[e[0] - 1][e[1] - 1] = true;
        graph[e[1] - 1][e[0] - 1] = true;
    }

    int longestDistance = bfs(n);

    int answer = 0;

    for(const auto &element : distances) {
        if(element == longestDistance) {
            answer++;
        }
    }

    return answer;
}