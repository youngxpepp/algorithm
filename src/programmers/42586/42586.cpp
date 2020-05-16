#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    while(!progresses.empty()) {
        int count = 0;
        vector<int> erased;
        vector<bool> deployed(progresses.size(), false);

        for(int i = 0; i < progresses.size(); i++) {
            progresses[i] += speeds[i];
            if(progresses[i] >= 100) {
                if(i == 0) {
                    answer.push_back(1);
                    erased.push_back(i);
                    deployed[i] = true;
                } else if(i > 0) {
                    if(progresses[i - 1] >= 100 && deployed[i - 1]) {
                        answer.back()++;
                        erased.push_back(i);
                        deployed[i] = true;
                    }
                }
            }
        }

        sort(erased.begin(), erased.end(), greater<int>());
        for(const auto element : erased) {
            progresses.erase(progresses.begin() + element);
            speeds.erase(speeds.begin() + element);
        }
    }
    
    return answer;
}