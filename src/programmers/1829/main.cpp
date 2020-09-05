#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int dfs(pair<int, int> position, vector<vector<int>> &picture, vector<vector<bool>> &visit) {
    visit[position.second][position.first] = true;

    int value = 0;

    for(int i = 0; i < 4; i++) {
        int nextX = position.first + directions[i].first;
        int nextY = position.second + directions[i].second;

        if(nextX < 0 || nextX >= visit.front().size() || nextY < 0 || nextY >= visit.size()) {
            continue;
        }

        if(visit[nextY][nextX]) {
            continue;
        }

        if(picture[nextY][nextX] != picture[position.second][position.first]) {
            continue;
        }

        value += dfs(make_pair(nextX, nextY), picture, visit);
    }

    return 1 + value;
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;

    vector<vector<bool>> visit(m, vector<bool>(n, false));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(picture[i][j] == 0) {
                continue;
            }

            if(visit[i][j]) {
                continue;
            }

            max_size_of_one_area = max(max_size_of_one_area, dfs(make_pair(j, i), picture, visit));
            number_of_area++;
        }
    }

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}