/*
ID: zhongbr1
TASK: fact4
LANG: C++14
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("fact4.in", "r", stdin);
    freopen("fact4.out", "w", stdout);

    int N;
    cin >> N;

    int cur = 1;
    for (int i=1; i<=N; i++) {
        cur *= i;
        cerr << cur << endl;
        while ((cur % 10) == 0) {
            cur /= 10;
        }
        cerr << cur << endl;
        cur %= 1000;
    }

    cout << cur % 10 << endl;
}
