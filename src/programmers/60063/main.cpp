#include <string>
#include <vector>
#include <queue>

using namespace std;

const int r[4] = {2, 3, 0, 1};
const int d[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int boardSize;
vector<vector<int>> globalBoard;
vector<vector<vector<vector<bool>>>> visit;

class Robot {
public:
    int x;
    int y;
    int direction;

    Robot(int _x, int _y, int _direction): x(_x), y(_y), direction(_direction) {}

    bool visited() {
        int _x = x + d[direction][0];
        int _y = y + d[direction][1];

        if(visit[y][x][_y][_x] || visit[_y][_x][y][x]) {
            return true;
        }

        return false;
    }

    void visitHere() {
        int _x = x + d[direction][0];
        int _y = y + d[direction][1];

        visit[y][x][_y][_x] = true;
        visit[_y][_x][y][x] = true;
    }

    bool arrived() {
        int _x = x + d[direction][0];
        int _y = y + d[direction][1];

        if(x == boardSize - 1 && y == boardSize - 1) {
            return true;
        }

        if(_x == boardSize - 1 && _y == boardSize - 1) {
            return true;
        }

        return false;
    }

    bool outOfTheBoard() {
        if(x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
            return true;
        }

        int _x = x + d[direction][0];
        int _y = y + d[direction][1];

        if(_x < 0 || _x >= boardSize || _y < 0 || _y >= boardSize) {
            return true;
        }

        return false;
    }

    bool onTheWall() {
        if(globalBoard[y][x] == 1) {
            return true;
        }

        int _x = x + d[direction][0];
        int _y = y + d[direction][1];

        if(globalBoard[_y][_x] == 1) {
            return true;
        }

        return false;
    }

    bool wallWhileTurning(int beforeDirection) {
        int wallX = x + d[beforeDirection][0] + d[direction][0];
        int wallY = y + d[beforeDirection][1] + d[direction][1];

        if(globalBoard[wallY][wallX] == 1) {
            return true;
        }

        return false;
    }

    bool goUp() {
        y -= 1;

        if(outOfTheBoard() || onTheWall() || visited()) {
            y += 1;
            return false;
        }

        visitHere();

        return true;
    }

    bool goDown() {
        y += 1;

        if(outOfTheBoard() || onTheWall() || visited()) {
            y -= 1;
            return false;
        }

        visitHere();

        return true;
    }

    bool goLeft() {
        x -= 1;

        if(outOfTheBoard() || onTheWall() || visited()) {
            x += 1;
            return false;
        }

        visitHere();

        return true;
    }

    bool goRight() {
        x += 1;

        if(outOfTheBoard() || onTheWall() || visited()) {
            x -= 1;
            return false;
        }

        visitHere();

        return true;
    }

    bool turnCounterClock() {
        int beforeDirection = direction;
        direction = (direction + 3) % 4;

        if(outOfTheBoard() || onTheWall() || wallWhileTurning(beforeDirection) || visited()) {
            direction = beforeDirection;
            return false;
        }

        visitHere();

        return true;
    }

    bool turnClock() {
        int beforeDirection = direction;
        direction = (direction + 1) % 4;

        if(outOfTheBoard() || onTheWall() || wallWhileTurning(beforeDirection) || visited()) {
            direction = beforeDirection;
            return false;
        }

        visitHere();

        return true;
    }

    bool turnCounterClockReverse() {
        int beforeX = x;
        int beforeY = y;
        int beforeDirection = direction;

        x += d[direction][0];
        y += d[direction][1];
        direction = r[direction];

        if(!turnCounterClock()) {
            x = beforeX;
            y = beforeY;
            direction = beforeDirection;
            return false;
        }

        return true;
    }

    bool turnClockReverse() {
        int beforeX = x;
        int beforeY = y;
        int beforeDirection = direction;

        x += d[direction][0];
        y += d[direction][1];
        direction = r[direction];

        if(!turnClock()) {
            x = beforeX;
            y = beforeY;
            direction = beforeDirection;
            return false;
        }

        return true;
    }


};

int bfs() {
    queue<pair<Robot, int>> bfsQueue;
    bfsQueue.push(make_pair(Robot(0, 0, 1), 0));

    while(!bfsQueue.empty()) {
        Robot newRobot = bfsQueue.front().first;
        int depth = bfsQueue.front().second;

        if(newRobot.arrived()) {
            return depth;
        }

        bfsQueue.pop();

        Robot nextRobot = newRobot;

        if(nextRobot.goUp()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.goDown()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.goLeft()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.goRight()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.turnClock()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.turnCounterClock()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.turnClockReverse()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
        if(nextRobot.turnCounterClockReverse()) {
            bfsQueue.push(make_pair(nextRobot, depth + 1));
            nextRobot = newRobot;
        }
    }
}

int solution(vector<vector<int>> board) {
    boardSize = board.size();
    globalBoard = board;
    visit.assign(board.size(), vector<vector<vector<bool>>>(board.size(), vector<vector<bool>>(board.size(), vector<bool>(board.size(), false))));

    int answer = bfs();
    return answer;
}