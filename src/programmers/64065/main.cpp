#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> solution(string s) {
    string copiedS = s;
    copiedS = copiedS.substr(1, s.size() - 2);

    vector<int> answer;
    set<int> mySet;
    vector<vector<int>> subsets;
    vector<int> indexStore(1000001, -1);

    string buffer = "";
    for(int i = 0; i < copiedS.size(); i++) {
        if(copiedS[i] == '{') {
           subsets.push_back(vector<int>());
           continue;
        }
        else if(copiedS[i - 1] == '}' && copiedS[i] == ',') {
            continue;
        }
        else if(copiedS[i] == ',') {
            subsets.back().push_back(stoi(buffer));
            buffer = "";
            continue;
        }
        else if(copiedS[i] == '}') {
            subsets.back().push_back(stoi(buffer));
            buffer = "";
            indexStore[subsets.back().size()] = subsets.size() - 1;
            continue;
        }

        buffer += copiedS[i];
    }

    for(int i = 1; i <= subsets.size(); i++) {
        vector<int> &subset = subsets[indexStore[i]];
        for(const auto element : subset) {
            if(mySet.find(element) == mySet.end()) {
                answer.push_back(element);
                mySet.insert(element);
            }
        }
    }

    return answer;
}
