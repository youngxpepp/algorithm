#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<char>> table;
vector<pair<int, int>> directions{{0,  -1},
                                  {0,  1},
                                  {-1, 0},
                                  {1,  0}};

class BfsNode {
public:
    int depth;
    pair<int, int> redBall;
    pair<int, int> blueBall;

    BfsNode(int depth, pair<int, int> redBall, pair<int, int> blueBall) : depth(depth),
                                                                          redBall(redBall),
                                                                          blueBall(blueBall) {}
};

pair<int, int> move(const pair<int, int> &_ball, int direction) {
    pair<int, int> ball = _ball;

    while (table[ball.second][ball.first] != 'O') {
        ball.first += directions[direction].first;
        ball.second += directions[direction].second;

        if (ball.first < 0 ||
            ball.first >= table.front().size() ||
            ball.second < 0 ||
            ball.second >= table.size() ||
            table[ball.second][ball.first] == '#') {

            ball.first -= directions[direction].first;
            ball.second -= directions[direction].second;
            return ball;
        }
    }

    return ball;
}

int bfs(const pair<int, int> _redBall, const pair<int, int> _blueBall) {
    queue<BfsNode> bfsQueue;
    bool visit[10][10][10][10] = {false,};
    bfsQueue.push(BfsNode(0, _redBall, _blueBall));

    while (!bfsQueue.empty()) {
        BfsNode bfsNode = bfsQueue.front();
        bfsQueue.pop();

        if(bfsNode.depth >= 10) {
            continue;
        }

        for (int i = 0; i < directions.size(); i++) {
            pair<int, int> nextRedBall = move(bfsNode.redBall, i);
            pair<int, int> nextBlueBall = move(bfsNode.blueBall, i);

            if (table[nextBlueBall.second][nextBlueBall.first] == 'O') {
                continue;
            }

            if (table[nextRedBall.second][nextRedBall.first] == 'O') {
                return bfsNode.depth + 1;
            }

            if (nextRedBall == nextBlueBall) {
                switch (i) {
                    case 0:
                        bfsNode.redBall.second > bfsNode.blueBall.second ? nextRedBall.second++ : nextBlueBall.second++;
                        break;
                    case 1:
                        bfsNode.redBall.second > bfsNode.blueBall.second ? nextBlueBall.second-- : nextRedBall.second--;
                        break;
                    case 2:
                        bfsNode.redBall.first > bfsNode.blueBall.first ? nextRedBall.first++ : nextBlueBall.first++;
                        break;
                    case 3:
                        bfsNode.redBall.first > bfsNode.blueBall.first ? nextBlueBall.first-- : nextRedBall.first--;
                        break;
                    default:;
                }
            }

            if(visit[nextRedBall.second][nextRedBall.first][nextBlueBall.second][nextBlueBall.first]) {
                continue;
            }

            visit[nextRedBall.second][nextRedBall.first][nextBlueBall.second][nextBlueBall.first] = true;
            bfsQueue.emplace(bfsNode.depth + 1, nextRedBall, nextBlueBall);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;
    cin >> n >> m;
    table.assign(n, vector<char>(m, 0));
    pair<int, int> redBall(0, 0);
    pair<int, int> blueBall(0, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
            if (table[i][j] == 'R') {
                redBall = {j, i};
                table[i][j] = '.';
            } else if (table[i][j] == 'B') {
                blueBall = {j, i};
                table[i][j] = '.';
            }
        }
    }

    cout << bfs(redBall, blueBall);

    return 0;
}
