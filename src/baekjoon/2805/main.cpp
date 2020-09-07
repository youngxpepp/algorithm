#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;

    cin >> n >> m;

    vector<int> trees(n, 0);

    for(int i = 0; i < n; i++) {
        cin >> trees[i];
    }

    sort(trees.begin(), trees.end());

    int left = 0;
    int right = trees.back() - 1;
    int answer = 0;

    while(left <= right) {
        int middle = (left + right) / 2;

        long long sum = 0;
        for(int i = 0; i < n; i++) {
            if(middle < trees[i]) {
                sum += (trees[i] - middle);
            }
        }

        if(sum >= m) {
            left = middle + 1;
            answer = max(answer, middle);
        } else {
            right = middle - 1;
        }
    }

    cout << answer;

    return 0;
}
