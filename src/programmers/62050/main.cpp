#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void bfsLand(vector<vector<int>> &land, vector<vector<int>> &area, int height, pair<int, int> start, int areaNumber) {
    queue<pair<int, int>> bfsQueue;
    bfsQueue.push(start);
    area[start.second][start.first] = areaNumber;

    while(!bfsQueue.empty()) {
        int x = bfsQueue.front().first;
        int y = bfsQueue.front().second;
        bfsQueue.pop();

        for(int i = 0; i < directions.size(); i++) {
            int newX = x + directions[i].first;
            int newY = y + directions[i].second;

            if(newX < 0 || newX >= land.size() || newY < 0 || newY >= land.size()) {
                continue;
            }

            if(area[newY][newX] != -1) {
                continue;
            }

            int heightDiff = abs(land[y][x] - land[newY][newX]);

            if(heightDiff > height) {
                continue;
            }

            area[newY][newX] = areaNumber;
            bfsQueue.push({newX, newY});
        }
    }
}

int getParent(int node, vector<int> &cycleTable) {
    if(cycleTable[node] == node) {
        return node;
    } else {
        return cycleTable[node] = getParent(cycleTable[node], cycleTable);
    }
}

class KruskalNode {
public:
    int a;
    int b;
    int distance;

    KruskalNode(int a, int b, int distance): a(a), b(b), distance(distance) {}

    bool operator<(const KruskalNode &target) const {
        return this->distance <= target.distance;
    }
};

int solution(vector<vector<int>> land, int height) {
    vector<vector<int>> area(land.size(), vector<int>(land.size(), -1));

    int areaNumber = 0;
    for(int i = 0; i < land.size(); i++) {
        for(int j = 0; j < land.size(); j++) {
            if(area[i][j] != - 1) {
                continue;
            }
            bfsLand(land, area, height, {j, i}, areaNumber++);
        }
    }

    set<KruskalNode> kruskalSet;

    for(int i = 0; i < land.size(); i++) {
        for(int j = 0; j < land.size(); j++) {
            for(int k = 0; k < 4; k++) {
                int x = j + directions[k].first;
                int y = i + directions[k].second;

                if(x < 0 || x >= land.size() || y < 0 || y >= land.size()) {
                    continue;
                }

                int firstArea = area[y][x];
                int secondArea = area[i][j];
                if(firstArea != secondArea) {
                    int distance = abs(land[i][j] - land[y][x]);
                    kruskalSet.insert(KruskalNode(firstArea, secondArea, distance));
                }
            }
        }
    }

    vector<int> cycleTable(areaNumber, 0);
    for(int i = 0; i < cycleTable.size(); i++) {
        cycleTable[i] = i;
    }

    int answer = 0;

    for(auto itr = kruskalSet.begin(); itr != kruskalSet.end(); itr++) {
        int aParent = getParent(itr->a, cycleTable);
        int bParent = getParent(itr->b, cycleTable);

        if(aParent == bParent) {
            continue;
        } else if(aParent < bParent) {
            cycleTable[bParent] = aParent;
        } else {
            cycleTable[aParent] = bParent;
        }

        answer += itr->distance;
    }

    return answer;
}
