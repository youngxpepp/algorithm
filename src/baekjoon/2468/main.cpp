#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> DIRECTIONS{{1,  0},
                                  {-1, 0},
                                  {0,  -1},
                                  {0,  1}};

void dfs(pair<int, int> p, int areaNumber, int height, vector<vector<int>> &areas, const vector<vector<int>> &matrix) {
    areas[p.second][p.first] = areaNumber;

    for (int i = 0; i < DIRECTIONS.size(); i++) {
        pair<int, int> next = p;
        next.first += DIRECTIONS[i].first;
        next.second += DIRECTIONS[i].second;

        if (next.first < 0 ||
            next.first >= matrix.size() ||
            next.second < 0 ||
            next.second >= matrix.size()) {

            continue;
        }

        if (areas[next.second][next.first] != -1) {
            continue;
        }

        if (matrix[next.second][next.first] <= height) {
            continue;
        }

        dfs(next, areaNumber, height, areas, matrix);
    }
}

int get_max_safe_area_count(const vector<vector<int>> &matrix, int highest) {
    int max_area_count = 0;
    for (int i = 0; i <= highest; i++) {
        vector<vector<int>> areas(matrix.size(), vector<int>(matrix.size(), -1));
        int areaNumber = 0;

        for (int j = 0; j < matrix.size(); j++) {
            for (int k = 0; k < matrix.size(); k++) {
                if (areas[j][k] != -1) {
                    continue;
                }

                if (matrix[j][k] <= i) {
                    continue;
                }

                dfs({k, j}, areaNumber++, i, areas, matrix);
            }
        }

        if (areaNumber > max_area_count) {
            max_area_count = areaNumber;
        }
    }
    return max_area_count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0, highest = 0;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];

            if (i == 0 && j == 0) {
                highest = matrix[0][0];
                continue;
            }

            if (matrix[i][j] > highest) {
                highest = matrix[i][j];
            }
        }
    }

    cout << get_max_safe_area_count(matrix, highest) << endl;

    return 0;
}
