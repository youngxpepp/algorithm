#include <iostream>
#include <cstdlib>

using namespace std;

long long solution(int width, int height) {
    long long howMany = 0;
    for(long long i = -width; i < height; i++) {
        long long firstOp = abs(width * (height - i));
        long long secondOp = width + height;

        if(firstOp % secondOp != 0) {
            howMany++;
        }
    }

    return (width * height) - howMany;
}

int main() {
    long long width, height;
    cin >> width >> height;

    cout << solution(width, height);

    return 0;
}