#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits.h>

using namespace std;

vector<vector<int>> cityGraph;
unordered_set<int> visit;


int dfs(int cityIndex, int distance, int startCityIndex) {
    if(distance != 0 && cityIndex == startCityIndex) {
        if(visit.size() == cityGraph.size()) {
            return distance;
        }

        return INT_MAX;
    }

    int value = INT_MAX;

    for(int i = 0; i < cityGraph[cityIndex].size(); i++) {
        if(cityGraph[cityIndex][i] == 0) {
            continue;
        }

        if(visit.find(i) != visit.end()) {
            continue;
        }

        visit.insert(i);
        value = min(value, dfs(i, distance + cityGraph[cityIndex][i], startCityIndex));
        visit.erase(i);
    }

    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    cityGraph.assign(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> cityGraph[i][j];
        }
    }

    cout << dfs(0, 0, 0);

    return 0;
}
