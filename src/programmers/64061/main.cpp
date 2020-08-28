#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;

    vector<stack<int>> boardStack(board.size(), stack<int>());
    stack<int> basket;

    for(auto itr = board.rbegin(); itr != board.rend(); itr++) {
        for(int i = 0; i < itr->size(); i++) {
            if(itr->at(i) == 0) {
                continue;
            }
            boardStack[i].push(itr->at(i));
        }
    }

    for(int i = 0; i < moves.size(); i++) {
        int index = moves[i] - 1;

        if(boardStack[index].empty()) {
            continue;
        }

        if(!basket.empty() && boardStack[index].top() == basket.top()) {
            boardStack[index].pop();
            basket.pop();
            answer += 2;
            continue;
        }

        basket.push(boardStack[index].top());
        boardStack[index].pop();
    }

    return answer;
}