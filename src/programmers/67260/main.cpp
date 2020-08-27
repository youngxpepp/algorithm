#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class CaveTravel {
public:
    vector<vector<int>> graph;
    vector<int> dfsVisit;
    vector<bool> dfsFinished;
    int dfsCount = 0;
    bool cycle = false;

    CaveTravel(int n, vector<vector<int>> path, vector<vector<int>> order) {
        this->graph.assign(n, vector<int>());
        this->dfsVisit.assign(n, -1);
        this->dfsFinished.assign(n, false);

        for(int i = 0; i < order.size(); i++) {
            graph[order[i][0]].push_back(order[i][1]);
        }

        vector<vector<int>> bidirectionalGraph(n, vector<int>());
        for(int i = 0; i < path.size(); i++) {
            bidirectionalGraph[path[i][0]].push_back(path[i][1]);
            bidirectionalGraph[path[i][1]].push_back(path[i][0]);
        }

        vector<bool> bfsVisit(n, false);
        queue<int> bfsQueue;
        bfsQueue.push(0);
        bfsVisit[0] = true;

        while(!bfsQueue.empty()) {
            int node = bfsQueue.front();
            bfsQueue.pop();

            for(int i = 0; i < bidirectionalGraph[node].size(); i++) {
                if(bfsVisit[bidirectionalGraph[node][i]]) {
                    continue;
                }

                bfsQueue.push(bidirectionalGraph[node][i]);
                this->graph[node].push_back(bidirectionalGraph[node][i]);
                bfsVisit[bidirectionalGraph[node][i]] = true;
            }
        }
    }

    void dfs(int node) {
        this->dfsVisit[node] = this->dfsCount++;

        for(int i = 0; i < this->graph[node].size(); i++) {
            if(this->cycle) {
                return;
            }

            // 트리 간선
            if(this->dfsVisit[this->graph[node][i]] == -1) {
                dfs(this->graph[node][i]);
            }
            // 순방향 간선
            else if(this->dfsVisit[this->graph[node][i]] > this->dfsVisit[node]) {
                continue;
            }
            // 역방향 간선
            else if(this->dfsVisit[this->graph[node][i]] < this->dfsVisit[node] && !this->dfsFinished[this->graph[node][i]]) {
                this->cycle = true;
                return;
            }
            // 교차 간선
            else {
                continue;
            }
        }

        this->dfsFinished[node] = true;
    }
};

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    CaveTravel caveTravel(n, path, order);
    caveTravel.dfs(0);
    return !caveTravel.cycle;
}