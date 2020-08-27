#include <string>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;

const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
const vector<vector<int>> DIRECTION_POSITION{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

class Car {
public:
    int x;
    int y;
    int direction = 0;
    int corners = 0;
    int distance = 0;

    Car(int x, int y): x(x), y(y) {}

    void move(int x, int y) {
        this->x += x;
        this->y += y;
    }

    int getPrice() {
        return (100 * distance) + (500 * corners);
    }
};

class DFS {
public:
    int lowestPrice = INT_MAX;
    vector<vector<int>> board;
    vector<vector<vector<int>>> visit;

    DFS(vector<vector<int>> board): board(board) {
        visit.assign(board.size(), vector<vector<int>>(board.size(), vector<int>(4, INT_MAX)));
    }

    void search(Car car) {
        if(car.x == this->board.size() - 1 && car.y == this->board.size() - 1) {
            this->lowestPrice = min(car.getPrice(), this->lowestPrice);
            return;
        }

        for(int i = 0; i < 4; i++) {
            Car nextCar = car;
            nextCar.move(DIRECTION_POSITION[i][0], DIRECTION_POSITION[i][1]);
            nextCar.direction = i;

            if(!this->validateCarPosition(nextCar)) {
                continue;
            }

            if(nextCar.getPrice() > this->lowestPrice) {
                continue;
            }

            if(nextCar.getPrice() >= this->visit[nextCar.y][nextCar.x][nextCar.direction]) {
                continue;
            }

            if(car.direction != i && !(car.x == 0 && car.y == 0)) {
                nextCar.corners++;
            }
            nextCar.distance++;

            this->visit[nextCar.y][nextCar.x][nextCar.direction] = nextCar.getPrice();
            search(nextCar);
        }
    }

    bool validateCarPosition(Car &car) {
        if(car.x < 0 || car.x >= this->board.size() || car.y < 0 || car.y >= this->board.size()) {
            return false;
        }

        if(this->board[car.y][car.x] == 1) {
            return false;
        }

        return true;
    }

    bool checkReversedDirections(int previousDirection, int currentDirection) {
        if(previousDirection + currentDirection == 1) {
            return true;
        } else if(previousDirection + currentDirection == 5) {
            return true;
        }

        return false;
    }
};

int solution(vector<vector<int>> board) {
    DFS dfs(board);
    dfs.search(Car(0, 0));
    return dfs.lowestPrice;
}
