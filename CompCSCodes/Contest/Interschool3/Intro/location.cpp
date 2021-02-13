//location.cpp created at 02/03/21 19:10:02

#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("location.in", "r", stdin);
    freopen("location.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    int x = 0, y = 0;
    for (int i=0; i<N; ++i) {
        char dir;
        cin >> dir;
        
        if (dir == 'U') ++y;
        else if (dir == 'D') --y;
        else if (dir == 'L') --x;
        else if (dir == 'R') ++x;
        else assert(false);
    }

    cout << x << ' ' << y << endl;
}

