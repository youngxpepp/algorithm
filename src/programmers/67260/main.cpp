#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool cycle = false;
int dfsCount = 0;
vector<vector<int>> graph;
vector<int> dfsVisit;
vector<bool> dfsFinished;

bool dfs(int nodeNumber) {
    dfsVisit[nodeNumber] = dfsCount++;

    bool value = true;

    for(int i = 0; i < graph[nodeNumber].size(); i++) {
        if(cycle) {
            return false;
        }

        int nextNodeNumber = graph[nodeNumber][i];

        if(dfsVisit[nextNodeNumber] == -1) {
            value = value & dfs(nextNodeNumber);
        }
        else if(dfsVisit[nextNodeNumber] > dfsVisit[nodeNumber]) {
            continue;
        }
        else if(dfsVisit[nextNodeNumber] < dfsVisit[nodeNumber] && !dfsFinished[nextNodeNumber]) {
            cycle = true;
            return false;
        }
        else {
            continue;
        }
    }
    dfsFinished[nodeNumber] = true;

    return value;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    vector<vector<int>> biGraph(n, vector<int>());
    graph.assign(n, vector<int>());

    for(auto & v : path) {
        biGraph[v[0]].push_back(v[1]);
        biGraph[v[1]].push_back(v[0]);
    }

    queue<int> bfsQueue;
    vector<bool> bfsVisit(n, false);
    bfsQueue.push(0);
    bfsVisit[0] = true;

    while(!bfsQueue.empty()) {
        int nodeNumber = bfsQueue.front();
        bfsQueue.pop();

        for(int i = 0; i < biGraph[nodeNumber].size(); i++) {
            if(bfsVisit[biGraph[nodeNumber][i]]) {
                continue;
            }

            bfsVisit[biGraph[nodeNumber][i]] = true;
            bfsQueue.push(biGraph[nodeNumber][i]);
            graph[nodeNumber].push_back(biGraph[nodeNumber][i]);
        }
    }

    for(auto & v : order) {
        graph[v[0]].push_back(v[1]);
    }

    dfsVisit.assign(n, -1);
    dfsFinished.assign(n, false);

    return dfs(0);
}