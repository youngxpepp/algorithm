#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    map<string, pair<int, int> > isComplete;
    for(const auto element : participant) {
        const auto& itr = isComplete.find(element);
        if(itr != isComplete.end()) {
            itr->second.first++;
        } else {
            isComplete.insert(make_pair(element, make_pair(1, 0)));
        }
    }

    for(const auto element : completion) {
        const auto& itr = isComplete.find(element);
        if(itr != isComplete.end()) {
            itr->second.second++;
        }
    }

    for(const auto& element : isComplete) {
        if(element.second.first != element.second.second) {
            return element.first;
        }
    }
}

int main() {
    return 0;
}