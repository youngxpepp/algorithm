#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <limits.h>
#include <functional>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = INT_MAX;

    int beginIndex = 0;
    map<int, int, greater<int>> myMap;

    for(int i = beginIndex; i < beginIndex + k; i++) {
        myMap[stones[i]]++;
    }

    while(beginIndex <= stones.size() - k) {
        if(beginIndex != 0) {
            myMap[stones[beginIndex + k - 1]]++;
        }

        answer = min(answer, myMap.begin()->first);

        const auto itr = myMap.find(stones[beginIndex]);
        if(--itr->second == 0) {
            myMap.erase(itr);
        }
        beginIndex++;
    }

    return answer;
}