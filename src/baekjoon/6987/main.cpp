#include <iostream>
#include <vector>

using namespace std;

vector<vector<vector<int>>> matrix(4, vector<vector<int>>(6, vector<int>(3, 0)));
vector<pair<int, int>> combinations;


void dfs_combination(int start, int count, vector<int> &combination) {
    if (count == 2) {
        combinations.emplace_back(combination[0], combination[1]);
        return;
    }

    for (int i = start; i < 6; i++) {
        combination.push_back(i);
        dfs_combination(i + 1, count + 1, combination);
        combination.pop_back();
    }
}

bool dfs(int count, vector<vector<int>> &m, vector<vector<int>> &t) {
    if (count == combinations.size()) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                if (m[i][j] != t[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool result = false;

    for (int i = 0; i < 3; i++) {
        pair<int, int> &p = combinations[count];
        m[p.first][i]++;
        m[p.second][2 - i]++;
        result |= dfs(count + 1, m, t);
        m[p.first][i]--;
        m[p.second][2 - i]--;
    }

    return result;
}

int is_possible(int matrix_number) {
    vector<vector<int>> m(6, vector<int>(3, 0));
    vector<vector<int>> &t = matrix[matrix_number];

    return dfs(0, m , t) ? 1 : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                cin >> matrix[i][j][k];
            }
        }
    }

    vector<int> a;
    dfs_combination(0, 0, a);

    for (int i = 0; i < 4; i++) {
        cout << is_possible(i) << ' ';
    }

    return 0;
}
