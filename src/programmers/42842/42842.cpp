#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    int xy = brown + yellow;

    int width = 0;
    int height = 0;

    for(int i = 1; i <= 2005000; i++) {
        if(xy % i != 0) {
            continue;
        }

        int j = xy / i;
        int brownNum = 2 * i + 2 * j - 4;

        if(i >= j && brownNum == brown) {
            width = i;
            height = j;
            break;
        }
    }
    
    vector<int> answer{width, height};

    return answer;
}