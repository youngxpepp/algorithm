#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    cin >> n >> k;

    vector<int> deviceOrder;
    for(int i = 0; i < k; i++) {
        int device = 0;
        cin >> device;
        deviceOrder.push_back(device);
    }

    int answer = 0;
    unordered_set<int> multiTap;

    for(int i = 0; i < k; i++) {
        if(multiTap.find(deviceOrder[i]) != multiTap.end()) {
            continue;
        }

        if(multiTap.size() < n) {
            multiTap.insert(deviceOrder[i]);
            continue;
        }

        multimap<int, int, greater<int>> mostFar;
        for(auto itr = multiTap.begin(); itr != multiTap.end(); itr++) {
            int near = k;
            for(int j = i + 1; j < k; j++) {
                if(deviceOrder[j] == *itr) {
                    near = j;
                    break;
                }
            }
            mostFar.insert(make_pair(near, *itr));
        }
        multiTap.erase(mostFar.begin()->second);
        multiTap.insert(deviceOrder[i]);
        answer++;
    }

    cout << answer;

    return 0;
}
