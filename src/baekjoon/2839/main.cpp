#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    if(n % 5 == 0) {
        cout << n / 5;
        return 0;
    }

    int quotent = n / 5;
    int number = 5 * quotent;
    while(number > 0) {
        if((n - number) % 3 == 0) {
            cout << quotent + (n - number) / 3;
            return 0;
        }
        number -= 5;
        quotent -= 1;
    }

    if(n % 3 == 0) {
        cout << n / 3;
        return 0;
    }

    cout << -1;

    return 0;
}
