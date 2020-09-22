#include <iostream>
#include <vector>
#include <set>
#include <limits.h>

using namespace std;

int n = 0, k = 0;
vector<int> coins;
vector<int> visit(10001, INT_MAX);

void dfs(int price, int count) {
    for(int i = 0; i < coins.size(); i++) {
        int nextPrice = price + coins[i];

        if(nextPrice > k) {
            continue;
        }

        if(count + 1 >= visit[nextPrice]) {
            continue;
        }

        visit[nextPrice] = count + 1;
        dfs(nextPrice, count + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    set<int> coinSet;
    for(int i = 0; i < n; i++) {
        int coin = 0;
        cin >> coin;
        coinSet.insert(coin);
    }

    for(auto itr = coinSet.rbegin(); itr != coinSet.rend(); itr++) {
        coins.push_back(*itr);
    }

    dfs(0, 0);

    if(visit[k] == INT_MAX) {
        cout << -1;
    } else {
        cout << visit[k];
    }

    return 0;
}
