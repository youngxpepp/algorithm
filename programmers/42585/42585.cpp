#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(string arrangement) {
    int answer = 0;
    
    vector<int> v;
    for(int i = 0; i < arrangement.size(); i++) {
        if(arrangement[i] == ')' && v.back() == -1) {
            v.pop_back();
            v.push_back(0);
        } else if(arrangement[i] == '(') {
            v.push_back(-1);
        } else if(arrangement[i] == ')') {
            v.push_back(1);
        }
    }
    
    vector<int> pipeLazer;

    for(int i = 0; i < v.size(); i++) {
        if(v[i] == -1) {
            pipeLazer.push_back(0);
        } else if(v[i] == 1) {
            answer += pipeLazer.back() + 1;
            pipeLazer.pop_back();
        } else if(v[i] == 0) {
            for(int j = 0; j < pipeLazer.size(); j++) {
                pipeLazer[j]++;
            }
        }
    }
    
    return answer;
}