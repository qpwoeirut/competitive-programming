//copymachine.cpp created at 11/12/20 11:45:53

#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
    freopen("copymachine.in", "r", stdin);
    freopen("copymachine.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        cout << x << '\n';
    }
}

