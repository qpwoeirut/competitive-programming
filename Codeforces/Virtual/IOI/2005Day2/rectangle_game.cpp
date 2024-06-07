#include <bits/stdc++.h>

using namespace std;

const int N = 500;
int to_win[N][N];
void brute() {
    for (int n=1; n<N; ++n) {
        cout << n << ": ";
        for (int m=1; m<N; ++m) {
            to_win[n][m] = 0;
            for (int i=(n + 1) / 2; i<n; ++i) {
                if (to_win[i][m] == 0 && (abs(to_win[n][m]) >= n - i || to_win[n][m] == 0)) to_win[n][m] = n - i;
            }
            for (int j=(m + 1) / 2; j<m; ++j) {
                if (to_win[n][j] == 0 && (abs(to_win[n][m]) >= m - j || to_win[n][m] == 0)) to_win[n][m] = j - m;
            }

            //string s = to_string(to_win[n][m]); while (s.size() < 3) s = ' ' + s; cout << s << ' ';
            if (to_win[n][m] == 0) cout << m << ' ';
            //cout << (to_win[n][m] == 0);
        }
        cout << endl;
    }
}

int find_losing(int a, int b) {
    int cur = b;
    while (cur > 1 && (cur & 1)) cur = (cur - 1) >> 1;

    while (cur < a) {
        if (2 * cur >= a) return cur;
        cur = 2 * cur + 1;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //brute(); return 0;

    int n, m;
    cin >> n >> m;
    do {
        const int losing_n = find_losing(n, m);
        const int losing_m = find_losing(m, n);

        assert(losing_n != -1 || losing_m != -1);
        if (losing_n != -1) {
            cout << "V " << n - losing_n << '\n';
        } else if (losing_m != -1) {
            cout << "H " << m - losing_m << '\n';
        } else assert(0);

        cout.flush();
        cin >> n >> m;
    } while (n > 0 && m > 0);
}
