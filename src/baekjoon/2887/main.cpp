#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int getParent(vector<int> &parents, int num) {
    if (parents[num] == num) {
        return num;
    } else {
        return parents[num] = getParent(parents, parents[num]);
    }
}

class planet {
public:
    int index;
    int x;
    int y;
    int z;

    planet(int index, int x, int y, int z) : index(index), x(x), y(y), z(z) {}

    int get_distance(const planet &t) {
        return min(min(abs(this->x - t.x), abs(this->y - t.y)), abs(this->z - t.z));
    }
};

bool compare_x(planet *&a, planet *&b) {
    return a->x < b->x;
}

bool compare_y(planet *&a, planet *&b) {
    return a->y < b->y;
}

bool compare_z(planet *&a, planet *&b) {
    return a->z < b->z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    cin >> n;

    vector<planet *> planets;
    planets.reserve(n);

    for (int i = 0; i < n; i++) {
        int x = 0, y = 0, z = 0;
        cin >> x >> y >> z;
        planets.push_back(new planet(i, x, y, z));
    }

    vector<planet *> planets_by_x = planets;
    vector<planet *> planets_by_y = planets;
    vector<planet *> planets_by_z = planets;

    sort(planets_by_x.begin(), planets_by_x.end(), compare_x);
    sort(planets_by_y.begin(), planets_by_y.end(), compare_y);
    sort(planets_by_z.begin(), planets_by_z.end(), compare_z);

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n - 1; i++) {
        edges.push_back({planets_by_x[i]->get_distance(*planets_by_x[i + 1]),
                         {planets_by_x[i]->index, planets_by_x[i + 1]->index}});
        edges.push_back({planets_by_y[i]->get_distance(*planets_by_y[i + 1]),
                         {planets_by_y[i]->index, planets_by_y[i + 1]->index}});
        edges.push_back({planets_by_z[i]->get_distance(*planets_by_z[i + 1]),
                         {planets_by_z[i]->index, planets_by_z[i + 1]->index}});
    }

    sort(edges.begin(), edges.end());

    vector<int> parents;
    parents.assign(n, 0);
    for (int i = 0; i < n; i++) {
        parents[i] = i;
    }
    int spanning_tree_cost = 0;

    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        int a_parent = getParent(parents, a);
        int b_parent = getParent(parents, b);

        if (a_parent < b_parent) {
            parents[b_parent] = a_parent;
        } else if (a_parent > b_parent) {
            parents[a_parent] = b_parent;
        } else {
            continue;
        }

        spanning_tree_cost += edges[i].first;
    }

    cout << spanning_tree_cost << endl;

    return 0;
}
