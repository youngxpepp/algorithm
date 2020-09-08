#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <limits.h>

using namespace std;

string findLru(unordered_map<string, int> &cache) {
    int minValue = INT_MAX;
    string minString = "";
    for(auto itr = cache.begin(); itr != cache.end(); itr++) {
        if(itr->second < minValue) {
            minString = itr->first;
            minValue = itr->second;
        }
    }

    return minString;
}

int solution(int cacheSize, vector<string> cities) {
    unordered_map<string, int> cache;

    int answer = 0;

    for(int i = 0; i < cities.size(); i++) {
        string cityName = cities[i];
        transform(cityName.begin(), cityName.end(), cityName.begin(), ::tolower);

        auto findCacheItr = cache.find(cityName);

        if(findCacheItr == cache.end()) {
            answer += 5;
            if(cache.size() < cacheSize) {
                cache[cityName] = i;
            } else if(cacheSize != 0) {
                string minString = findLru(cache);
                cache.erase(minString);
                cache[cityName] = i;
            }
        } else {
            answer += 1;
            findCacheItr->second = i;
        }
    }

    return answer;
}