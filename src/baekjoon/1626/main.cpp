#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

int v = 0, e = 0;
vector<int> parents;
vector<tuple<int, int, int>> kruskalVector;

int getParent(int num) {
    if (parents[num] == num) {
        return num;
    } else {
        return parents[num] = getParent(parents[num]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;

    parents.assign(v, 0);

    for (int i = 0; i < v; i++) {
        parents[i] = i;
    }

    for (int i = 0; i < e; i++) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        a--;
        b--;

        kruskalVector.emplace_back(c, a, b);
    }

    sort(kruskalVector.begin(), kruskalVector.end());

    vector<int> kruskalIndex;

    for (int j = 0; j < kruskalVector.size(); j++) {
        int aParent = getParent(get<1>(kruskalVector[j]));
        int bParent = getParent(get<2>(kruskalVector[j]));

        if (aParent < bParent) {
            parents[bParent] = aParent;
            kruskalIndex.push_back(j);
        } else if (bParent < aParent) {
            parents[aParent] = bParent;
            kruskalIndex.push_back(j);
        }
    }

    for (int j = 0; j < parents.size(); j++) {
        if (getParent(j) != getParent(0)) {
            cout << -1;
            return 0;
        }
    }

    for (int i = 0; i < v; i++) {
        parents[i] = i;
    }

    set<long long> distances;

    for (int i = kruskalIndex.size() - 1; i >= 0 ; i--) {
        long long distance = 0;
        for (int j = 0; j < kruskalVector.size(); j++) {
            if (j == kruskalIndex[i]) {
                continue;
            }

            int aParent = getParent(get<1>(kruskalVector[j]));
            int bParent = getParent(get<2>(kruskalVector[j]));

            if (aParent < bParent) {
                parents[bParent] = aParent;
                distance += get<0>(kruskalVector[j]);
            } else if (bParent < aParent) {
                parents[aParent] = bParent;
                distance += get<0>(kruskalVector[j]);
            }
        }

        bool isSpanningTree = true;
        for (int j = 0; j < parents.size(); j++) {
            if (getParent(j) != getParent(0)) {
                isSpanningTree = false;
                break;
            }
        }

        if (isSpanningTree) {
            cout << distance;
            return 0;
        }

        for (int i = 0; i < v; i++) {
            parents[i] = i;
        }
    }

    if (distances.empty()) {
        cout << -1;
    } else {
        cout << *distances.begin();
    }

    return 0;
}
