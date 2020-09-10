#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    cin >> n >> k;

    vector<pair<int, int>> gems;
    vector<int> bags;

    for(int i = 0; i < n; i++) {
        int weight = 0, price = 0;
        cin >> weight >> price;
        gems.emplace_back(weight, price);
    }

    for(int i = 0; i < k; i++) {
        int bagMaxWeight = 0;
        cin >> bagMaxWeight;
        bags.push_back(bagMaxWeight);
    }

    sort(gems.begin(), gems.end());
    sort(bags.begin(), bags.end());

    multiset<int, greater<int>> gemSet;
    int startIndex = 0;
    long long answer = 0;
    for(int i = 0; i < k; i++) {
        while(startIndex < n && gems[startIndex].first <= bags[i]) {
            gemSet.insert(gems[startIndex].second);
            startIndex++;
        }

        if(!gemSet.empty()) {
            answer += (long long)*gemSet.begin();
            gemSet.erase(gemSet.begin());
        }
    }

    cout << answer;

    return 0;
}
