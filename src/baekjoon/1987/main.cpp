#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

class Horse {
public:
    int x;
    int y;
    int distance = 0;

    Horse(int x, int y, int distance): x(x), y(y), distance(distance) {}

    void move(int direction) {
        this->x += directions[direction].first;
        this->y += directions[direction].second;
        this->distance++;
    }
};

int dfs(Horse horse, vector<vector<char>> &board, vector<bool> &visit) {
    int maxValue = 0;

    for(int i = 0; i < directions.size(); i++) {
        Horse nextHorse = horse;
        nextHorse.move(i);

        if(nextHorse.x < 0 || nextHorse.x >= board.front().size() || nextHorse.y < 0 || nextHorse.y >= board.size()) {
            continue;
        }

        if(visit[board[nextHorse.y][nextHorse.x] - 'A']) {
            continue;
        }

        visit[board[nextHorse.y][nextHorse.x] - 'A'] = true;
        maxValue = max(maxValue, dfs(nextHorse, board, visit));
        visit[board[nextHorse.y][nextHorse.x] - 'A'] = false;
    }

    if(maxValue == 0) {
        return horse.distance;
    }

    return maxValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r = 0, c = 0;
    cin >> r >> c;

    vector<vector<char>> board(r, vector<char>());

    for(int i = 0; i < r; i++) {
        string input = "";
        cin >> input;
        for(int j = 0; j < input.size(); j++) {
            board[i].push_back(input[j]);
        }
    }

    vector<bool> visit(26, false);
    visit[board[0][0] - 'A'] = true;
    cout << dfs(Horse(0, 0, 1), board, visit);

    return 0;
}
