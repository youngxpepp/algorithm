#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    multiset<int> q;

    for(const auto& operation : operations) {
        if(operation[0] == 'I') {
            string numString = operation.substr(2, operation.size() - 2);
            int num = stoi(numString);
            q.insert(num);
        } else if(operation[0] == 'D' && !q.empty()) {
            if(operation[2] == '1') {
                auto itr = q.end();
                itr--;
                q.erase(itr);
            } else if(operation[2] == '-') {
                q.erase(q.begin());
            }
        }
    }

    if(q.empty()) {
        answer.push_back(0);
        answer.push_back(0);
        return answer;
    }

    auto itr = q.end();
    itr--;
    answer.push_back(*itr);
    answer.push_back(*q.begin());

    return answer;
}