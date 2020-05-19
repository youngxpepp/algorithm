#include <iostream>
#include <vector>

using namespace std;

int N, M;

void dfs(vector<int>& arr, vector<bool> visit, int depth) {
    if(depth >= M) {
        for(const auto& element : arr) {
            cout << element << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = 1; i <= N; i++) {
        if(visit[i]) {
            continue;
        }
        arr[depth] = i;
        visit[i] = true;
        dfs(arr, visit, depth + 1);
        visit[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    vector<bool> visit(N + 1, false);
    vector<int> arr(M, 0);

    dfs(arr, visit, 0);

    return 0;
}