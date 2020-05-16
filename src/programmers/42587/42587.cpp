#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

int solution(vector<int> priorities, int location) {
    if(priorities.size() == 1) {
        return 1;
    }
    
    multiset<int> prioritySet;
    queue<pair<int, int> > q;
    vector<int> order;

    for(int i = 0; i < priorities.size(); i++) {
        prioritySet.insert(priorities[i]);
        q.push(make_pair(priorities[i], i));
    }

    while(!q.empty()) {
        if(prioritySet.upper_bound(q.front().first) != prioritySet.end()) {
            q.push(q.front());
            q.pop();
        } else {
            prioritySet.erase(--prioritySet.end());
            order.push_back(q.front().second);
            q.pop();
            if(order.back() == location) {
                return order.size();
            }
        }
    }
}