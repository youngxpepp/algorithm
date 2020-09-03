#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

class KruskalNode {
public:
    int a;
    int b;
    double distance;

    KruskalNode(int a, int b, double distance): a(a), b(b), distance(distance) {}

    bool operator<(const KruskalNode &target) const {
        return this->distance <= target.distance;
    }
};

class Position {
public:
    int x;
    int y;

    Position(int x, int y): x(x), y(y) {}

    double getDistance(Position &target) {
        double resultX = pow(abs(this->x - target.x), 2);
        double resultY = pow(abs(this->y - target.y), 2);

        return sqrt(resultX + resultY);
    }
};

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

    vector<Position> positions;

    for(int i = 0; i < n; i++) {
        int x = 0, y = 0;
        cin >> x >> y;

        positions.push_back(Position(x, y));
    }

    double distance = 0;
    vector<int> cycleTable(n, 0);

    for(int i = 0; i < n; i++) {
        cycleTable[i] = i;
    }

    for(int i = 0; i < m; i++) {
        int a = 0, b = 0;
        cin >> a >> b;

        a--; b--;

        int aParent = getParent(a, cycleTable);
        int bParent = getParent(b, cycleTable);

        if(aParent < bParent) {
            cycleTable[bParent] = aParent;
        } else if(aParent > bParent) {
            cycleTable[aParent] = bParent;
        }
    }

    set<KruskalNode> kruskalArr;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            kruskalArr.insert(KruskalNode(i, j, positions[i].getDistance(positions[j])));
        }
    }

    int count = m;
    for(auto itr = kruskalArr.begin(); itr != kruskalArr.end(); itr++) {
        int aParent = getParent(itr->a, cycleTable);
        int bParent = getParent(itr->b, cycleTable);

        if(aParent < bParent) {
            cycleTable[bParent] = aParent;
            distance += itr->distance;
        } else if(aParent > bParent) {
            cycleTable[aParent] = bParent;
            distance += itr->distance;
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << distance << endl;

    return 0;
}
