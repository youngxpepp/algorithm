#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Food {
public:
    int key;
    int time;

    Food(int key, int time) {
        this->key = key;
        this->time = time;
    }
};

bool compareFoodByTimeDesc(const Food &a, const Food &b) {
    if(a.time == b.time) {
        return a.key < b.key;
    }
    return a.time > b.time;
}

bool compareFoodByKeyAsc(const Food &a, const Food &b) {
    return a.key < b.key;
}

int solution(vector<int> food_times, long long k) {
    vector<Food> foods;

    for(int i = 0; i < food_times.size(); i++) {
        foods.push_back(Food(i + 1, food_times[i]));
    }

    sort(foods.begin(), foods.end(), compareFoodByTimeDesc);

    int previousTime = 0;
    while(true) {
        if(!foods.empty() && (foods.back().time - previousTime) * foods.size() <= k) {
            k -= (foods.back().time - previousTime) * foods.size();
            previousTime = foods.back().time;
            foods.pop_back();
        } else {
          break;
        }
    }

    if(foods.empty()) {
        return -1;
    }

    sort(foods.begin(), foods.end(), compareFoodByKeyAsc);

    return foods[k % foods.size()].key;
}