#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    long long sum = 0;
    while (N--) {
        int x;
        cin >> x;
        sum += x;
    }

    cout << sum << endl;
}
