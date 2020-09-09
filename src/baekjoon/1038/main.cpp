#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

vector<char> numbers{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void changeVectorToInteger(vector<int> &numberVector) {
    for(int i = 0; i < numberVector.size(); i++) {
        cout << numberVector[i];
    }
    cout << endl;
}

void bfs(int n) {
    queue<vector<int>> bfsQueue;
    bfsQueue.push(vector<int>());

    int count = -1;
    while(!bfsQueue.empty()) {
        vector<int> now = bfsQueue.front();
        bfsQueue.pop();

        if(!now.empty() && now[0] == 0) {
            continue;
        }

        int endIndex = 10;

        if(!now.empty()) {
            endIndex = now.back();
        }

        for(int i = 0; i < endIndex; i++) {
            count++;
            now.push_back(i);

            if(count == n) {
                changeVectorToInteger(now);
                return;
            }

            bfsQueue.push(now);
            now.pop_back();
        }
    }

    cout << -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    bfs(n);

    return 0;
}
