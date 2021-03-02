#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int get_how_many_viruses(const vector<vector<int>> &net, int start) {
    int result = 0;

    vector<bool> visit(net.size(), false);
    queue<int> q;
    visit[start] = true;
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < net[now].size(); i++) {
            int next = net[now][i];
            if (visit[next]) {
                continue;
            }
            result++;
            visit[next] = true;
            q.push(next);
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m = 0, n = 0;
    cin >> m >> n;
    vector<vector<int>> network(m, vector<int>());

    for (int i = 0; i < n; i++) {
        int a = 0, b = 0;
        cin >> a >> b;
        a--;
        b--;
        network[a].push_back(b);
        network[b].push_back(a);
    }

    cout << get_how_many_viruses(network, 0) << endl;

    return 0;
}
