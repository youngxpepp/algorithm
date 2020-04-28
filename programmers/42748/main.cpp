#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;

    for(const auto& command : commands) {
        vector<int> v;
        int start = command[0] - 1;
        int end = command[1] - 1;
        
        for(int i = start; i <= end; i++) {
            v.push_back(array[i]);
        }

        sort(v.begin(), v.end());
        answer.push_back(v[command[2] - 1]);
    }

    return answer;
}