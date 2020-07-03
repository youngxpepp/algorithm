#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool exist(vector<vector<int>>& buildings, int x, int y, int a) {
    for(const auto& v : buildings) {
        if(v[0] == x && v[1] == y && v[2] == a) {
            return true;
        }
    }

    return false;
}

int whereExists(vector<vector<int>>& buildings, int x, int y, int a) {
    for(int i = 0; i < buildings.size(); i++) {
        const auto& v = buildings[i];
        if(v[0] == x && v[1] == y && v[2] == a) {
            return i;
        }
    }

    return -1;
}

bool isBuildPossible(vector<vector<int>>& buildings, int x, int y, int a) {
    if(a == 0) {
        bool onTheGround = y == 0;
        bool onThePlate = exist(buildings, x, y, 1) || exist(buildings, x - 1, y, 1);
        bool onThePole = exist(buildings, x, y - 1, 0);

        if(!onTheGround && !onThePlate && !onThePole) {
            return false;
        }
    }
    else if(a == 1) {
        bool nextToThePole = exist(buildings, x, y - 1, 0) || exist(buildings, x + 1, y - 1, 0);
        bool twoPlates = exist(buildings, x - 1, y, 1) && exist(buildings, x + 1, y, 1);

        if(!nextToThePole && !twoPlates) {
            return false;
        }
    }

    return true;
}

void build(vector<vector<int>>& buildings, int x, int y, int a) {
    if(!isBuildPossible(buildings, x, y, a)) {
        return;
    }

    vector<int> building;
    building.push_back(x);
    building.push_back(y);
    building.push_back(a);

    buildings.push_back(building);
}

void destroy(vector<vector<int>>& buildings, int x, int y, int a) {
    int index = whereExists(buildings, x, y, a);
    buildings.erase(buildings.begin() + index);

    if(a == 0) {
        if(exist(buildings, x, y + 1, 1) && !isBuildPossible(buildings, x, y + 1, 1)) {
            buildings.push_back({x, y, a});
            return;
        }

        if(exist(buildings, x - 1, y + 1, 1) && !isBuildPossible(buildings, x - 1, y + 1, 1)) {
            buildings.push_back({x, y, a});
            return;
        }

        if(exist(buildings, x, y + 1, 0) && !isBuildPossible(buildings, x, y + 1, 0)) {
            buildings.push_back({x, y, a});
            return;
        }
    }
    else if(a == 1) {
        if(exist(buildings, x, y, 0) && !isBuildPossible(buildings, x, y, 0)) {
            buildings.push_back({x, y, a});
            return;
        }

        if(exist(buildings, x + 1, y, 0) && !isBuildPossible(buildings, x + 1, y, 0)) {
            buildings.push_back({x, y, a});
            return;
        }

        if(exist(buildings, x - 1, y, 1) && !isBuildPossible(buildings, x - 1, y, 1)) {
            buildings.push_back({x, y, a});
            return;
        }

        if(exist(buildings, x + 1, y, 1) && !isBuildPossible(buildings, x + 1, y, 1)) {
            buildings.push_back({x, y, a});
            return;
        }
    }
}

void buildOrDestroy(vector<vector<int>>& buildings, int x, int y, int a, int b) {
    if(b == 0) {
        destroy(buildings, x, y, a);
    } else if(b == 1) {
        build(buildings, x, y, a);
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    for(const auto& v : build_frame) {
        buildOrDestroy(answer, v[0], v[1], v[2], v[3]);
    }

    sort(answer.begin(), answer.end());

    return answer;
}

int main() {
    return 0;
}
