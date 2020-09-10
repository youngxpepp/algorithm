#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> words;

int dfs(int depth, int k, vector<bool> &visit, int alphabet) {
    if(depth == k) {
        int count = 0;
        for(int i = 0; i < words.size(); i++) {
            if(words[i].size() == 8) {
                count++;
                continue;
            }

            bool condition = true;
            for(int j = 4; j < 4 + (words[i].size() - 8); j++) {
                if(!visit[words[i][j] - 'a']) {
                    condition = false;
                    break;
                }
            }

            if(condition) {
                count++;
            }
        }

        return count;
    }

    int value = 0;

    int beginIndex = -1;
    if(depth > 5) {
        beginIndex = alphabet;
    }

    for(int i = beginIndex + 1; i < 26; i++) {
        if(visit[i]) {
            continue;
        }

        visit[i] = true;
        value = max(value, dfs(depth + 1, k, visit, i));
        visit[i] = false;
    }

    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    cin >> n >> k;

    words.assign(n, "");

    for(int i = 0; i < n; i++) {
        cin >> words[i];
    }

    if(k < 5) {
        cout << 0;
        return 0;
    }

    vector<bool> visit(26, false);
    visit['a' - 'a'] = true;
    visit['c' - 'a'] = true;
    visit['i' - 'a'] = true;
    visit['n' - 'a'] = true;
    visit['t' - 'a'] = true;

    cout << dfs(5, k, visit, -1);

    return 0;
}
