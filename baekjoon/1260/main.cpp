#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, V;
vector<int>* GRAPH;
vector<bool> DFS_VISIT;
vector<bool> BFS_VISIT;
queue<int> BFS_QUEUE;

void dfs(int start) {
    cout << start << " ";
    DFS_VISIT[start] = true;
    for(int i = 0; i < GRAPH[start].size(); i++) {
        int next = GRAPH[start][i];
        if(!DFS_VISIT[next]) {
            dfs(next);
        }
    }
}

void bfs(int start) {
    BFS_QUEUE.push(start);
    BFS_VISIT[start] = true;
    while(!BFS_QUEUE.empty()) {
        int now = BFS_QUEUE.front();
        BFS_QUEUE.pop();
        cout << now << " ";
        for(int i = 0; i < GRAPH[now].size(); i++) {
            if(!BFS_VISIT[GRAPH[now][i]]) {
                BFS_QUEUE.push(GRAPH[now][i]);
                BFS_VISIT[GRAPH[now][i]] = true;
            }
        }
    }
}

int main()
{
    cin >> N >> M >> V;
    GRAPH = new vector<int>[N + 1];
    DFS_VISIT.assign(N + 1, false);
    BFS_VISIT.assign(N + 1, false);

    for(int i = 0; i < M; i++) {
        int firstEdge, secondEdge;
        cin >> firstEdge >> secondEdge;
        GRAPH[firstEdge].push_back(secondEdge);
        GRAPH[secondEdge].push_back(firstEdge);
    }

    for(int i = 1; i < N + 1; i++) {
        sort(GRAPH[i].begin(), GRAPH[i].end());
    }

    dfs(V);
    cout << endl;
    bfs(V);

    return 0;
}