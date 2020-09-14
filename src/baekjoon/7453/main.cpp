#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    vector<vector<int>> numbers(4, vector<int>(n, 0));

    for(int i = 0; i < n; i++) {
        cin >> numbers[0][i] >> numbers[1][i] >> numbers[2][i] >> numbers[3][i];
    }

    vector<int> ab;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ab.push_back(numbers[0][i] + numbers[1][j]);
        }
    }

    sort(ab.begin(), ab.end());

    long long answer = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int cdSum = numbers[2][i] + numbers[3][j];
            answer += upper_bound(ab.begin(), ab.end(), -cdSum) - lower_bound(ab.begin(), ab.end(), -cdSum);
        }
    }

    cout << answer;

    return 0;
}
