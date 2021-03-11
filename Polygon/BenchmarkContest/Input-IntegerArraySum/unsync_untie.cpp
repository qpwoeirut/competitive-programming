#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    long long sum = 0;

    while (N--) {
        int x;
        cin >> x;
        sum += x;
    }

    cout << sum << '\n';
}
