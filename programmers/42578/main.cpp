#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    map<string, int> clothesMap;
    for(const auto element : clothes) {
        const auto& itr = clothesMap.find(element[1]);
        if(itr != clothesMap.end()) {
            itr->second++;
        } else {
            clothesMap.insert(make_pair(element[1], 1));
        }
    }


    int answer = 1;
    for(const auto& element : clothesMap) {
        answer *= (element.second + 1);
    }

    return answer - 1;
}