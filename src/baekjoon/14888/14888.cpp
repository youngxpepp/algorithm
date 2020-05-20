#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N;
vector<int> V;
vector<int> OPERATOR_COUNT;
set<int> ANSWER;

void dfs(vector<int> operators, int depth) {
    if(depth >= N - 1) {
        int result = V[0];
        for(int i = 1; i < V.size(); i++) {
            switch(operators[i - 1]) {
                case 0:
                    result += V[i];
                    break;
                case 1:
                    result -= V[i];
                    break;
                case 2:
                    result *= V[i];
                    break;
                case 3:
                    result /= V[i];
                    break;
                default:
                    break;
            }
        }
        ANSWER.insert(result);
        return;
    }

    for(int i = 0; i < 4; i++) {
        if(OPERATOR_COUNT[i] == 0) {
            continue;
        }
        operators.push_back(i);
        OPERATOR_COUNT[i]--;
        dfs(operators, depth + 1);
        OPERATOR_COUNT[i]++;
        operators.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    V.assign(N, 0);
    OPERATOR_COUNT.assign(4, 0);

    for(auto& element : V) {
        cin >> element;
    }
    for(auto& element : OPERATOR_COUNT) {
        cin >> element;
    }

    dfs(vector<int>(), 0);

    if(ANSWER.size() == 1) {
        cout << *ANSWER.begin() << endl;
        cout << *ANSWER.begin() << endl;
    } else {
        auto itr = ANSWER.end();
        cout << *(--itr) << endl;
        cout << *ANSWER.begin() << endl;
    }


    return 0;
}