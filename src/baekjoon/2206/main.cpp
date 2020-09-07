#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits.h>

using namespace std;

const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

class Node {
public:
    int x;
    int y;
    int distance = 1;
    int removedCount = 0;

    Node(int x, int y): x(x), y(y) {}

    void move(int direction) {
        this->x += directions[direction].first;
        this->y += directions[direction].second;
        this->distance += 1;
    }
};

void dfs(Node node, vector<vector<int>> &myMap, vector<vector<vector<int>>> &visit) {
    if(node.x == myMap.front().size() - 1 && node.y == myMap.size() - 1) {
        return;
    }

    for(int i = 0; i < directions.size(); i++) {
        Node nextNode = node;
        nextNode.move(i);

        if(nextNode.x < 0 || nextNode.x >= myMap.front().size() || nextNode.y < 0 || nextNode.y >= myMap.size()) {
            continue;
        }

        if(nextNode.distance >= visit[nextNode.y][nextNode.x][nextNode.removedCount]) {
            continue;
        }

        if(myMap[nextNode.y][nextNode.x] == 1) {
            if(nextNode.removedCount > 0) {
                continue;
            }
            nextNode.removedCount++;
        }

        visit[nextNode.y][nextNode.x][nextNode.removedCount] = nextNode.distance;
        dfs(nextNode, myMap, visit);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;
    vector<vector<int>> myMap(n, vector<int>());
    for(int i = 0; i < n; i++) {
        string input = "";
        cin >> input;
        for(int j = 0; j < m; j++) {
            myMap[i].push_back(input[j] - '0');
        }
    }

    vector<vector<vector<int>>> visit(n, vector<vector<int>>(m, vector<int>(2, INT_MAX)));
    visit[0][0][0] = 1;
    visit[0][0][1] = 1;
    dfs(Node(0, 0), myMap, visit);

    if(visit[n - 1][m - 1][0] == INT_MAX && visit[n - 1][m - 1][1] == INT_MAX) {
        cout << -1;
    } else {
        cout << min(visit[n - 1][m - 1][0], visit[n - 1][m - 1][1]);
    }

    return 0;
}
