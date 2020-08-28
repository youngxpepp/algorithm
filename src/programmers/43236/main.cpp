#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance);

    int answer = 0;
    int left = 0, right = distance;

    while(left <= right) {
        int minDistance = (left + right) / 2;
        int previous = 0;
        int removeCount = 0;

        for(int i = 0; i < rocks.size(); i++) {
            if((rocks[i] - previous) < minDistance) {
                removeCount++;
            } else {
                previous = rocks[i];
            }
        }

        if(removeCount <= n) {
            answer = max(answer, minDistance);
            left = minDistance + 1;
        } else {
            right = minDistance - 1;
        }
    }

    return answer;
}