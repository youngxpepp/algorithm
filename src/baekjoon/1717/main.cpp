#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int getParent(int num, vector<int> &parents) {
    if(num == parents[num]) {
        return num;
    } else {
        return parents[num] = getParent(parents[num], parents);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;

    vector<int> parents(n + 1, 0);
    for(int i = 0; i < parents.size(); i++) {
        parents[i] = i;
    }

    for(int i = 0; i < m; i++) {
        int a[3]{0, 0, 0};

        cin >> a[0] >> a[1] >> a[2];

        if(a[0] == 0) {
            int aParent = getParent(a[1], parents);
            int bParent = getParent(a[2], parents);

            if(aParent < bParent) {
                parents[bParent] = aParent;
            } else if(aParent > bParent) {
                parents[aParent] = bParent;
            }
        }
        else if(a[0] == 1) {
            if(getParent(a[1], parents) == getParent(a[2], parents)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
