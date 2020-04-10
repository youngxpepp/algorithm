#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer;
    for(int i = 0; i < heights.size(); i++) {
        int idx = -1;
        for(int j = i; j >= 0; j--) {
            if(heights[j] > heights[i]) {
                idx = j;
                break;
            }
        }
        if(idx != -1) {
            answer.push_back(idx + 1);
        } else {
            answer.push_back(0);
        }
    }

    return answer;
}