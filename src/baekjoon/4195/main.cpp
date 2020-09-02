#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

pair<string, int> getParent(string name, unordered_map<string, pair<string ,int>> &parents) {
    if(name == parents[name].first) {
        return parents[name];
    } else {
        return parents[name] = getParent(parents[name].first, parents);
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int testCaseNumber = 0;
    cin >> testCaseNumber;

    for(int i = 0; i < testCaseNumber; i++) {
        int friendRelations = 0;
        cin >> friendRelations;

        unordered_map<string, pair<string, int>> parents;

        for(int j = 0; j < friendRelations; j++) {
            string a = "", b = "";

            cin >> a >> b;

            if(parents.find(a) == parents.end()) {
                parents[a] = make_pair(a, 1);
            }

            if(parents.find(b) == parents.end()) {
                parents[b] = make_pair(b, 1);
            }

            pair<string, int> aParent = getParent(a, parents);
            pair<string, int> bParent = getParent(b, parents);

            if(aParent.first < bParent.first) {
                aParent.second += bParent.second;
                parents[aParent.first].second = aParent.second;
                parents[bParent.first] = aParent;

                cout << aParent.second << "\n";
            } else if(aParent.first > bParent.first) {
                bParent.second += aParent.second;
                parents[aParent.first] = bParent;
                parents[bParent.first].second = bParent.second;

                cout << bParent.second << "\n";
            } else {
                cout << aParent.second << "\n";
            }
        }
    }

    return 0;
}
