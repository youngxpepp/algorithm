#include <iostream>
#include <vector>

using namespace std;

int HOW_MANY_WAYS = 0;
int HOUSE_SIZE;
vector<vector<int> > HOUSE;

struct Position
{
    int x;
    int y;
    Position(int _x, int _y) : x(_x), y(_y) {}
};

struct Pipe
{
    Position position;
    int mode;

    Pipe(Position _position, int _mode) : position(_position), mode(_mode) {}
};

void dfs(Pipe pipe)
{
    int mode = pipe.mode;
    int x = pipe.position.x;
    int y = pipe.position.y;

    if (x == HOUSE_SIZE && y == HOUSE_SIZE)
    {
        HOW_MANY_WAYS++;
        return;
    }

    if (mode == 0)
    {
        // mode: 0 -> 0
        if (x + 1 <= HOUSE_SIZE && HOUSE[y][x + 1] == 0)
        {
            dfs(Pipe(Position(x + 1, y), 0));
        }

        // mode: 0 -> 2
        if (x + 1 <= HOUSE_SIZE && y + 1 <= HOUSE_SIZE && HOUSE[y][x + 1] == 0 && HOUSE[y + 1][x] == 0 && HOUSE[y + 1][x + 1] == 0)
        {
            dfs(Pipe(Position(x + 1, y + 1), 2));
        }
    }
    else if (mode == 1)
    {
        // mode: 1 -> 1
        if (y + 1 <= HOUSE_SIZE && HOUSE[y + 1][x] == 0)
        {
            dfs(Pipe(Position(x, y + 1), 1));
        }

        // mode: 1 -> 2
        if (x + 1 <= HOUSE_SIZE && y + 1 <= HOUSE_SIZE && HOUSE[y][x + 1] == 0 && HOUSE[y + 1][x] == 0 && HOUSE[y + 1][x + 1] == 0)
        {
            dfs(Pipe(Position(x + 1, y + 1), 2));
        }
    }
    else if (mode == 2)
    {
        // mode: 2 -> 0
        if (x + 1 <= HOUSE_SIZE && HOUSE[y][x + 1] == 0)
        {
            dfs(Pipe(Position(x + 1, y), 0));
        }

        // mode: 2 -> 1
        if (y + 1 <= HOUSE_SIZE && HOUSE[y + 1][x] == 0)
        {
            dfs(Pipe(Position(x, y + 1), 1));
        }

        // mode: 2 -> 2
        if (x + 1 <= HOUSE_SIZE && y + 1 <= HOUSE_SIZE && HOUSE[y][x + 1] == 0 && HOUSE[y + 1][x] == 0 && HOUSE[y + 1][x + 1] == 0)
        {
            dfs(Pipe(Position(x + 1, y + 1), 2));
        }
    }

    return;
}

int main()
{
    cin >> HOUSE_SIZE;
    HOUSE.assign(HOUSE_SIZE + 1, vector<int>(HOUSE_SIZE + 1, 0));
    for (int i = 1; i < HOUSE_SIZE + 1; i++)
    {
        for (int j = 1; j < HOUSE_SIZE + 1; j++)
        {
            cin >> HOUSE[i][j];
        }
    }

    dfs(Pipe(Position(2, 1), 0));

    cout << HOW_MANY_WAYS << endl;

    return 0;
}