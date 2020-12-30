#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n = 0;
bool arr[25][25]{false};
int count_arr[25][25]{0};
pair<int, int> directions[] = {{1,  0},
                               {-1, 0},
                               {0,  -1},
                               {0,  1}};

int dfs(pair<int, int> start, int count_number) {
    int count = 1;

    for (int i = 0; i < 4; i++) {
        pair<int, int> nextStart = {start.first + directions[i].first, start.second + directions[i].second};

        if (nextStart.first < 0 || nextStart.first >= n || nextStart.second < 0 || nextStart.second >= n) {
            continue;
        }

        if (!arr[nextStart.second][nextStart.first]) {
            continue;
        }

        if (count_arr[nextStart.second][nextStart.first] != 0) {
            continue;
        }

        count_arr[nextStart.second][nextStart.first] = count_number;
        count += dfs(nextStart, count_number);
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        string input = "";
        cin >> input;
        for (int j = 0; j < input.size(); j++) {
            if (input[j] == '0') {
                arr[i][j] = false;
            } else if (input[j] == '1') {
                arr[i][j] = true;
            }
        }
    }

    int count_number = 1;
    vector<int> sorted;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!arr[i][j]) {
                continue;
            }
            if (count_arr[i][j] != 0) {
                continue;
            }
            count_arr[i][j] = count_number;
            int result = dfs({j, i}, count_number++);
            sorted.push_back(result);
        }
    }

    sort(sorted.begin(), sorted.end());

    cout << count_number - 1 << '\n';
    for (auto e : sorted) {
        cout << e << '\n';
    }

    return 0;
}
