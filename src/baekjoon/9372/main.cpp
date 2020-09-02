#include <iostream>
#include <vector>

using namespace std;

int getParent(int num, vector<int> &parents) {
    if(num == parents[num]) {
        return num;
    } else {
        return parents[num] = getParent(parents[num], parents);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int testCase = 0;
    cin >> testCase;

    for(int i = 0; i < testCase; i++) {
        int countryCount = 0, planeCount = 0;

        cin >> countryCount >> planeCount;

        vector<vector<bool>> graph(countryCount, vector<bool>(countryCount, false));

        for(int j = 0; j < planeCount; j++) {
            int a = 0, b = 0;
            cin >> a >> b;

            graph[a - 1][b - 1] = true;
            graph[b - 1][a - 1] = true;
        }

        vector<int> cycleTable(countryCount, 0);
        for(int j = 0; j < countryCount; j++) {
            cycleTable[j] = j;
        }

        int count = 0;
        for(int j = 0; j < countryCount; j++) {
            for(int k = j + 1; k < countryCount; k++) {
                if(graph[j][k]) {
                    int jParent = getParent(j, cycleTable);
                    int kParent = getParent(k, cycleTable);

                    if(jParent < kParent) {
                        cycleTable[kParent] = jParent;
                        count++;
                    } else if(jParent > kParent) {
                        cycleTable[jParent] = kParent;
                        count++;
                    }
                }
            }
        }

        cout << count << "\n";
    }

    return 0;
}
