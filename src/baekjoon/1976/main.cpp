#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getParent(int num, vector<int> &parents) {
    if(num == parents[num]) {
        return num;
    } else {
        return parents[num] = getParent(parents[num], parents);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;

    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<int> cities(m, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < m; i++) {
        cin >> cities[i];
        cities[i]--;
    }

    vector<int> parents(n, 0);
    for(int i = 0; i < parents.size(); i++) {
        parents[i] = i;
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(graph[i][j] != 1) {
                continue;
            }

            int iParent = getParent(i, parents);
            int jParent = getParent(j, parents);

            if(iParent < jParent) {
                parents[jParent] = iParent;
            }
            else if(iParent > jParent) {
                parents[iParent] = jParent;
            }
        }
    }

    for(int i = 0; i < m - 1; i++) {
        if(getParent(cities[i], parents) != getParent(cities[i + 1], parents)) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";

    return 0;
}
