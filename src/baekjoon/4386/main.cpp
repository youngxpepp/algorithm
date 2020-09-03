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
        return this->distance < target.distance;
    }
};

class Position {
public:
    double x;
    double y;

    Position(double x, double y): x(x), y(y) {}

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

    int starNumber = 0;
    cin >> starNumber;

    vector<Position> stars;

    for(int i = 0; i < starNumber; i++) {
        double x = 0;
        double y = 0;

        cin >> x >> y;

        stars.push_back(Position(x, y));
    }

    set<KruskalNode> kruskalArr;

    for(int i = 0; i < starNumber; i++) {
        for(int j = i + 1; j < starNumber; j++) {
            kruskalArr.insert(KruskalNode(i, j, stars[i].getDistance(stars[j])));
        }
    }

    vector<int> cycleTable(starNumber, 0);

    for(int i = 0; i < starNumber; i++) {
        cycleTable[i] = i;
    }

    double minDistance = 0;
    for(auto itr = kruskalArr.begin(); itr != kruskalArr.end(); itr++) {
        const int aParent = getParent(itr->a, cycleTable);
        const int bParent = getParent(itr->b, cycleTable);

        if(aParent < bParent) {
            cycleTable[bParent] = aParent;
            minDistance += itr->distance;
        } else if(aParent > bParent) {
            cycleTable[aParent] = bParent;
            minDistance += itr->distance;
        }
    }

    cout << minDistance << "\n";

    return 0;
}
