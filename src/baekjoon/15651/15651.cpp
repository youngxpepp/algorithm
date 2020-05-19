#include <iostream>
#include <vector>

using namespace std;

int N, M;

void dfs(vector<int>& arr, int depth) {
    if(depth >= M) {
        for(const auto& element : arr) {
            cout << element << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = 1; i <= N; i++) {
        arr[depth] = i;
        dfs(arr, depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    vector<int> arr(M, 0);

    dfs(arr, 0);

    return 0;
}