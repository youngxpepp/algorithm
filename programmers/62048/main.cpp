#include <iostream>

using namespace std;

long long solution(int width, int height) {
    int howMany = height + width - 1;
    for(int i = 1; i < width; i++) {
        int remain = (i * (long long)height) % width;
        if(remain == 0) {
            howMany--;
        }
    }

    return ((long long)width * height) - howMany;
}

int main() {
    long long width, height;
    cin >> width >> height;

    cout << solution(width, height);

    return 0;
}