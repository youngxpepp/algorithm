#include <iostream>
#include <vector>
#include <set>

using namespace std;

class KruskalNode {
public:
    int a;
    int b;
    int distance;

    KruskalNode(int a, int b, int distance): a(a), b(b), distance(distance) {}

    bool operator==(const KruskalNode &target) {
        return this->a == target.a && this->b == target.b;
    }

    bool operator<(const KruskalNode &target) const {
        return this->distance <= target.distance;
    }
};

int getParent(int n, vector<int> &parents) {
    if(n == parents[n]) {
        return n;
    } else {
        return parents[n] = getParent(parents[n], parents);
    }
}

int main() {
    int v = 0, e = 0;

    cin >> v >> e;

    set<KruskalNode> kruskalNodeSet;

    for(int i = 0; i < e; i++) {
        int input[3]{0, 0, 0};

        cin >> input[0] >> input[1] >> input[2];

        kruskalNodeSet.insert(KruskalNode(input[0] - 1, input[1] - 1, input[2]));
    }

    vector<int> cycleTable(v, 0);

    for(int i = 0; i < v; i++) {
        cycleTable[i] = i;
    }

    int edge = 0;

    for(auto itr = kruskalNodeSet.begin(); itr != kruskalNodeSet.end(); itr++) {
        int aParent = getParent(itr->a, cycleTable);
        int bParent = getParent(itr->b, cycleTable);

        if(aParent < bParent) {
            cycleTable[bParent] = aParent;
            edge += itr->distance;
        } else if(aParent > bParent) {
            cycleTable[aParent] = bParent;
            edge += itr->distance;
        }
    }

    cout << edge << "\n";

    return 0;
}
