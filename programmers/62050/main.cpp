#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

struct Position {
    int x;
    int y;
    Position(int _x, int _y): x(_x), y(_y) {}
};

const int MAX_HEIGHT = 10000;
int HEIGHT;
int LAND_LENGTH;
int LAND_SIZE;
int GROUP_COUNT = 0;
vector<vector<int> > LAND;
vector<vector<int> > GROUPS;
vector<vector<int> > GRAPH;

void partialBfs(Position start) {
    queue<Position> bfsQueue;
    bfsQueue.push(start);
    int groupNum = GROUP_COUNT;
    GROUPS[start.y][start.x] = groupNum;

    while(!bfsQueue.empty()) {
        int x = bfsQueue.front().x;
        int y = bfsQueue.front().y;

        bfsQueue.pop();

        // up
        if(y - 1 >= 0 && GROUPS[y - 1][x] == -1 && abs(LAND[y][x] - LAND[y - 1][x]) <= HEIGHT) {
            bfsQueue.push(Position(x, y - 1));
            GROUPS[y - 1][x] = groupNum;
        }

        // down
        if(y + 1 < LAND_LENGTH && GROUPS[y + 1][x] == -1 && abs(LAND[y][x] - LAND[y + 1][x]) <= HEIGHT) {
            bfsQueue.push(Position(x, y + 1));
            GROUPS[y + 1][x] = groupNum;
        }
        
        // left
        if(x - 1 >= 0 && GROUPS[y][x - 1] == -1 && abs(LAND[y][x] - LAND[y][x - 1]) <= HEIGHT) {
            bfsQueue.push(Position(x - 1, y));
            GROUPS[y][x - 1] = groupNum;
        }

        // right
        if(x + 1 < LAND_LENGTH && GROUPS[y][x + 1] == -1 && abs(LAND[y][x] - LAND[y][x + 1]) <= HEIGHT) {
            bfsQueue.push(Position(x + 1, y));
            GROUPS[y][x + 1] = groupNum;
        }

    }
    GROUP_COUNT++;
}

void entireBfs(Position start) {
    queue<Position> bfsQueue;
    bfsQueue.push(start);
    vector<vector<bool> > visit(LAND_LENGTH, vector<bool>(LAND_LENGTH, false));
    visit[start.y][start.x] = true;

    while(!bfsQueue.empty()) {
        int x = bfsQueue.front().x;
        int y = bfsQueue.front().y;

        bfsQueue.pop();

        // up
        if(y - 1 >= 0 && !visit[y - 1][x]) {
            if(GROUPS[y][x] != GROUPS[y - 1][x]) {
                GRAPH[GROUPS[y][x]][GROUPS[y - 1][x]] = min(GRAPH[GROUPS[y][x]][GROUPS[y - 1][x]], abs(LAND[y][x] - LAND[y - 1][x]));
                GRAPH[GROUPS[y - 1][x]][GROUPS[y][x]] = GRAPH[GROUPS[y][x]][GROUPS[y - 1][x]];
            }
            visit[y - 1][x] = true;
            bfsQueue.push(Position(x, y - 1));
        }

        // down
        if(y + 1 < LAND_LENGTH && !visit[y + 1][x]) {
            if(GROUPS[y][x] != GROUPS[y + 1][x]) {
                GRAPH[GROUPS[y][x]][GROUPS[y + 1][x]] = min(GRAPH[GROUPS[y][x]][GROUPS[y + 1][x]], abs(LAND[y][x] - LAND[y + 1][x]));
                GRAPH[GROUPS[y + 1][x]][GROUPS[y][x]] = GRAPH[GROUPS[y][x]][GROUPS[y + 1][x]];
            }
            visit[y + 1][x] = true;
            bfsQueue.push(Position(x, y + 1));
        }

        // left
        if(x - 1 >= 0 && !visit[y][x - 1]) {
            if(GROUPS[y][x] != GROUPS[y][x - 1]) {
                GRAPH[GROUPS[y][x]][GROUPS[y][x - 1]] = min(GRAPH[GROUPS[y][x]][GROUPS[y][x - 1]], abs(LAND[y][x] - LAND[y][x - 1]));
                GRAPH[GROUPS[y][x - 1]][GROUPS[y][x]] = GRAPH[GROUPS[y][x]][GROUPS[y][x - 1]];
            }
            visit[y][x - 1] = true;
            bfsQueue.push(Position(x - 1, y));
        }

        // right
        if(x + 1 < LAND_LENGTH && !visit[y][x + 1]) {
            if(GROUPS[y][x] != GROUPS[y][x + 1]) {
                GRAPH[GROUPS[y][x]][GROUPS[y][x + 1]] = min(GRAPH[GROUPS[y][x]][GROUPS[y][x + 1]], abs(LAND[y][x] - LAND[y][x + 1]));
                GRAPH[GROUPS[y][x + 1]][GROUPS[y][x]] = GRAPH[GROUPS[y][x]][GROUPS[y][x + 1]];
            }
            visit[y][x + 1] = true;
            bfsQueue.push(Position(x + 1, y));
        }
    }
}

int prim(int start) {
    int ladderCost = 0;
    int ladderCount = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<bool> visit(GROUP_COUNT, false);
    visit[start] = true;

    for(int i = 0; i < GROUP_COUNT; i++) {
        if(start == i || GRAPH[start][i] == MAX_HEIGHT) continue;
        pq.push(make_pair(GRAPH[start][i], i));
    }

    while(!pq.empty() || ladderCount != GROUP_COUNT - 1) {
        int cost = pq.top().first;
        int vertex = pq.top().second;

        pq.pop();

        if(visit[vertex]) continue;
        
        ladderCount++;
        ladderCost += cost;
        visit[vertex] = true;

        for(int i = 0; i < GROUP_COUNT; i++) {
            if(vertex == i && GRAPH[vertex][i] == MAX_HEIGHT) continue;
            pq.push(make_pair(GRAPH[vertex][i], i));
        }
    }

    return ladderCost;
}

int solution(vector<vector<int> > land, int height) {
    HEIGHT = height;
    LAND = land;
    LAND_LENGTH = land.size();
    LAND_SIZE = (int)pow(land.size(), 2);

    GROUPS.assign(LAND_LENGTH, vector<int>(LAND_LENGTH, -1));

    for(int i = 0; i < LAND_LENGTH; i++) {
        for(int j = 0; j < LAND_LENGTH; j++) {
            if(GROUPS[i][j] == -1) {
                partialBfs(Position(j, i));
            }
        }
    }

    GRAPH.assign(GROUP_COUNT, vector<int>(GROUP_COUNT, MAX_HEIGHT));

    entireBfs(Position(0, 0));
    
    return prim(0);
}

int main() {
    int n, h;
    cin >> n >> h;
    vector<vector<int> > land(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> land[i][j];
        }
    }

    cout << solution(land, h) << endl;

    return 0;
}
