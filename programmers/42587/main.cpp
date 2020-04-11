#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>

using namespace std;

int solution(vector<int> priorities, int location) {
    if(priorities.size() == 1) {
        return 1;
    }
    
    int answer = location;
    multiset<int> prioritySet;

    for(int i = 0; i < priorities.size(); i++) {
        prioritySet.insert(priorities[i]);
    }

    int index = 0;
    while(index < priorities.size()) {
        if(prioritySet.upper_bound(priorities[index]) != prioritySet.end()) {
            if(index == answer) {
                answer = priorities.size() - 1;
            } else {
                answer--;
            }

            priorities.push_back(priorities[index]);
            priorities.erase(priorities.begin() + index);
        } else {
            if(index == answer) {
                break;
            }
            auto itr = prioritySet.end();
            prioritySet.erase(--itr);
            index++;
        }
    }

    return answer + 1;
}

int main() {
    vector<int> p;
    p.push_back(1);
    p.push_back(1);
    p.push_back(9);
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    solution(p, 0);
    
    return 0;
}