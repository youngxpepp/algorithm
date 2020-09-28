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

    while (ball.first >= 0 && ball.first < table.front().size() &&
           ball.second >= 0 && ball.second < table.size() &&
           table[ball.second][ball.first] != '#' &&
           table[ball.second][ball.first] != 'O') {
        ball.first += directions[direction].first;
        ball.second += directions[direction].second;
    }

    if (ball.first < 0 ||
        ball.first >= table.front().size() ||
        ball.second < 0 ||
        ball.second >= table.size() ||
        table[ball.second][ball.first] == '#') {

        ball.first -= directions[direction].first;
        ball.second -= directions[direction].second;
    }

    return ball;
}

int bfs(const pair<int, int> _redBall, const pair<int, int> _blueBall) {
    queue<BfsNode> bfsQueue;
    bfsQueue.push(BfsNode(0, _redBall, _blueBall));

    while (!bfsQueue.empty()) {
        BfsNode bfsNode = bfsQueue.front();
        bfsQueue.pop();

        for (int i = 0; i < directions.size(); i++) {
            pair<int, int> nextRedBall = bfsNode.redBall;
            pair<int, int> nextBlueBall = bfsNode.blueBall;

            pair<int, int> left = move(nextRedBall, i);
            pair<int, int> right = move(nextBlueBall, i);

            if (i == 0) {
                if (left == right && table[left.second][left.first] != 'O') {
                    if(nextRedBall.second > nextBlueBall.second) {
                        nextBlueBall = move(nextBlueBall, i);
                        nextRedBall = nextBlueBall;
                        nextRedBall.second -= directions[i].second;
                    } else {
                        nextRedBall = move(nextRedBall, i);
                        nextBlueBall = nextRedBall;
                        nextBlueBall.second -= directions[i].second;
                    }
                } else {
                    nextRedBall = move(nextRedBall, i);
                    nextBlueBall = move(nextBlueBall, i);
                }
            } else if (i == 1) {
                if (left == right && table[left.second][left.first] != 'O') {
                    if(nextRedBall.second > nextBlueBall.second) {
                        nextRedBall = move(nextRedBall, i);
                        nextBlueBall = nextRedBall;
                        nextBlueBall.second -= directions[i].second;
                    } else {
                        nextBlueBall = move(nextBlueBall, i);
                        nextRedBall = nextBlueBall;
                        nextRedBall.second -= directions[i].second;
                    }
                } else {
                    nextRedBall = move(nextRedBall, i);
                    nextBlueBall = move(nextBlueBall, i);
                }
            } else if (i == 2) {
                if (left == right && table[left.second][left.first] != 'O') {
                    if(nextRedBall.first > nextBlueBall.first) {
                        nextBlueBall = move(nextBlueBall, i);
                        nextRedBall = nextBlueBall;
                        nextRedBall.first -= directions[i].first;
                    } else {
                        nextRedBall = move(nextRedBall, i);
                        nextBlueBall = nextRedBall;
                        nextBlueBall.first -= directions[i].first;
                    }
                } else {
                    nextRedBall = move(nextRedBall, i);
                    nextBlueBall = move(nextBlueBall, i);
                }
            } else if (i == 3) {
                if (left == right && table[left.second][left.first] != 'O') {
                    if(nextRedBall.first > nextBlueBall.first) {
                        nextRedBall = move(nextRedBall, i);
                        nextBlueBall = nextRedBall;
                        nextBlueBall.first -= directions[i].first;
                    } else {
                        nextBlueBall = move(nextBlueBall, i);
                        nextRedBall = nextBlueBall;
                        nextRedBall.first -= directions[i].first;
                    }
                } else {
                    nextRedBall = move(nextRedBall, i);
                    nextBlueBall = move(nextBlueBall, i);
                }
            }

            if (table[nextBlueBall.second][nextBlueBall.first] == 'O') {
                continue;
            }

            if (table[nextRedBall.second][nextRedBall.first] == 'O') {
                return bfsNode.depth + 1;
            }

            if(bfsNode.depth >= 9) {
                continue;
            }

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

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            cout << table[i][j] << " ";
//        }
//        cout << endl;
//    }

    cout << bfs(redBall, blueBall);

    return 0;
}
