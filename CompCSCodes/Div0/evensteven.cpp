//evensteven.cpp created at 11/12/20 11:43:58

#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
    freopen("evensteven.in", "r", stdin);
    freopen("evensteven.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=2; i<=N; i+=2) {
        cout << i << '\n';
    }
}

