#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
int k;

int bfs() {
    vector<bool> visit(100001, false);
    queue<pair<int, int> > bfsQueue;
    bfsQueue.push(make_pair(n, 0));

    while(!bfsQueue.empty()) {
        int position = bfsQueue.front().first;
        int depth = bfsQueue.front().second;

        if(position == k) {
            return depth;
        }

        bfsQueue.pop();

        if(position - 1 >= 0 && position - 1 <= 100000 && !visit[position - 1]) {
            if(position - 1 == k) {
                return depth + 1;
            }

            bfsQueue.push(make_pair(position - 1, depth + 1));
            visit[position - 1] = true;
        }

        if(position + 1 >= 0 && position + 1 <= 100000 && !visit[position + 1]) {
            if(position + 1 == k) {
                return depth + 1;
            }
            
            bfsQueue.push(make_pair(position + 1, depth + 1));
            visit[position + 1] = true;
        }

        if(position * 2 >= 0 && position * 2 <= 100000 && !visit[position * 2]) {
            if(position * 2 == k) {
                return depth + 1;
            }

            bfsQueue.push(make_pair(position * 2, depth + 1));
            visit[position * 2] = true;
        }
    }
}

int main() {
    cin >> n >> k;

    cout << bfs();

    return 0;
}