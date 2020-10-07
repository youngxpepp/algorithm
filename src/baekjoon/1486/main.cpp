#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

int n = 0, m = 0, t = 0, d = 0;
vector<vector<int>> mountain;
vector<vector<long long>> floydWarshallVector;
const vector<pair<int, int>> directions{{0,  -1},
                                        {0,  1},
                                        {-1, 0},
                                        {1,  0}};

int getPositionNumber(pair<int, int> position) {
    return (position.second * m) + position.first;
}

pair<int, int> getPosition(int number) {
    return {number % m, number / m};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> t >> d;

    mountain.assign(n, vector<int>(m, 0));
    floydWarshallVector.assign(n * m, vector<long long>(n * m, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char input = ' ';
            cin >> input;

            if (input >= 'a') {
                input = input - 'a' + 26;
            } else {
                input -= 'A';
            }

            mountain[i][j] = input;
        }
    }

    for (int i = 0; i < floydWarshallVector.size(); i++) {
        floydWarshallVector[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int nowHeight = mountain[i][j];
            for (int k = 0; k < directions.size(); k++) {
                pair<int, int> nextPosition(j + directions[k].first, i + directions[k].second);

                if (nextPosition.first < 0 ||
                    nextPosition.first >= m ||
                    nextPosition.second < 0 ||
                    nextPosition.second >= n) {
                    continue;
                }

                int distance = 0;
                int nextHeight = mountain[nextPosition.second][nextPosition.first];

                if (abs(nextHeight - nowHeight) > t) {
                    continue;
                }

                if (nextHeight > nowHeight) {
                    distance += pow(nextHeight - nowHeight, 2);
                } else {
                    distance += 1;
                }

                int from = getPositionNumber({j, i});
                int to = getPositionNumber(nextPosition);

                floydWarshallVector[from][to] = distance;
            }
        }
    }

    for (int i = 0; i < floydWarshallVector.size(); i++) {
        for (int j = 0; j < floydWarshallVector.size(); j++) {
            for (int k = 0; k < floydWarshallVector.size(); k++) {
                if (floydWarshallVector[j][k] > floydWarshallVector[j][i] + floydWarshallVector[i][k]) {
                    floydWarshallVector[j][k] = floydWarshallVector[j][i] + floydWarshallVector[i][k];
                }
            }
        }
    }

    vector<int> results;

    for (int i = 0; i < floydWarshallVector.size(); i++) {
        long long distance = floydWarshallVector[0][i] + floydWarshallVector[i][0];

        if (distance > d) {
            continue;
        }

        pair<int, int> position = getPosition(i);

        results.push_back(mountain[position.second][position.first]);
    }

    sort(results.begin(), results.end(), greater<>());

    cout << results.front();

    return 0;
}
