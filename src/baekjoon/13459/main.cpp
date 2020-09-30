#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int bfs(int n, int k) {
    queue<pair<int, int>> bfsQueue;
    vector<int> visit(100001, INT_MAX);

    bfsQueue.emplace(0, n);
    visit[n] = 0;

    while (!bfsQueue.empty()) {
        int t = bfsQueue.front().first;
        int nn = bfsQueue.front().second;
        bfsQueue.pop();

        if (nn == k) {
            return t;
        }

        int left = nn - 1;
        int right = nn + 1;
        int warp = 2 * nn;

        if (warp >= 0 && warp <= 100000 && t < visit[warp]) {
            visit[warp] = t;
            bfsQueue.emplace(t, warp);
        }

        if (left >= 0 && left <= 100000 && t + 1 < visit[left]) {
            visit[left] = t + 1;
            bfsQueue.emplace(t + 1, left);
        }

        if (right >= 0 && right <= 100000 && t + 1 < visit[right]) {
            visit[right] = t + 1;
            bfsQueue.emplace(t + 1, right);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    cin >> n >> k;

    cout << bfs(n, k);

    return 0;
}
