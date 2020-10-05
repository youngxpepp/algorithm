#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int n = 0, m = 0;
vector<vector<int>> graph;

int dfs(int start, int depth, vector<bool> &visit) {
    int childCount = 1;

    for (int i = 0; i < graph[start].size(); i++) {
        int nodeNumber = graph[start][i];

        if (visit[nodeNumber]) {
            continue;
        }

        visit[nodeNumber] = true;
        childCount += dfs(nodeNumber, depth + 1, visit);
    }

    return childCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    graph.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0;
        cin >> a >> b;
        a--;
        b--;

        graph[b].push_back(a);
    }

    map<int, set<int>, greater<>> numberMap;

    for (int i = 0; i < n; i++) {
        vector<bool> visit(n, false);
        visit[i] = true;

        int count = dfs(i, 0, visit);

        auto itr = numberMap.find(count);
        if (itr == numberMap.end()) {
            numberMap.emplace(count, set<int>{i});
        } else {
            numberMap[count].insert(i);
        }
    }

    set<int> &firstSet = numberMap.begin()->second;

    for (auto itr = firstSet.begin(); itr != firstSet.end(); itr++) {
        cout << *itr + 1 << " ";
    }

    return 0;
}
