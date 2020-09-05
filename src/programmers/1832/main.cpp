#include <iostream>
#include <vector>

using namespace std;

int MOD = 20170805;

int dp(int x, int y, int direction, vector<vector<int>> &cityMap, vector<vector<vector<int>>> &cache) {
    if(cache[y][x][direction] != -1) {
       return cache[y][x][direction];
    }

    int value = 0;

    if(direction == 0 && x - 1 >= 0) {
        if(cityMap[y][x - 1] == 0) {
            if(x - 1 == 0 && y == 0) {
                value++;
            } else {
                value += dp(x - 1, y, 0, cityMap, cache);
                value += dp(x - 1, y, 1, cityMap, cache);
            }
        } else if(cityMap[y][x - 1] == 2) {
            value += dp(x - 1, y, direction, cityMap, cache);
        }
    }

    if(direction == 1 && y - 1 >= 0) {
        if(cityMap[y - 1][x] == 0) {
            if(x == 0 && y - 1 == 0) {
                value++;
            } else {
                value += dp(x, y - 1, 0, cityMap, cache);
                value += dp(x, y - 1, 1, cityMap, cache);
            }
        } else if(cityMap[y - 1][x] == 2) {
            value += dp(x, y - 1, direction, cityMap, cache);
        }
    }

    cache[y][x][direction] = value % MOD;
    return value % MOD;
}

int solution(int m, int n, vector<vector<int>> city_map) {
    vector<vector<vector<int>>> cache(m, vector<vector<int>>(n, vector<int>(2, -1)));
    return (dp(n - 1, m - 1, 0, city_map, cache) + dp(n - 1, m - 1, 1, city_map, cache)) % MOD;
}
