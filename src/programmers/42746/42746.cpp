#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool compare(const string& a, const string& b) {
    int left = stoi(a + b);
    int right = stoi(b + a);

    return left > right;
}  

string solution(vector<int> numbers) {
    vector<string> c;
    bool isAllZero = true;
    for(const auto element : numbers) {
        if(element != 0) {
            isAllZero = false;
        }
        c.push_back(to_string(element));
    }

    if(isAllZero) {
        return "0";
    }
    
    sort(c.begin(), c.end(), compare);

    string answer = "";
    for(const auto element : c) {
        answer += element;
    }

    return answer;
}    
