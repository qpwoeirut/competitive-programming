/*
ID: zhongbr1
TASK: kimbits
LANG: C++14
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll choose[32][32];
ll opts[32][32];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("kimbits.in", "r", stdin);
    freopen("kimbits.out", "w", stdout);

    ll  N, L, I;
    cin >> N >> L >> I;

    for (int i=0; i<=N; i++) {
        choose[i][0] = 1;
        for (int j=1; j<=N; j++) {
            choose[i][j] = choose[i][j-1] * (i-j+1) / j; 
        }
    }
    for (int i=0; i<=N; i++) {
        for (int j=0; j<=N; j++) {
            opts[i][j] = choose[i][j];
            if (j > 0) opts[i][j] += opts[i][j-1];
        }
    }

    string ans = "";
    for (int i=0; i<N; i++) {
        if (opts[N-i-1][L] < I) {
            I -= opts[N-i-1][L];
            --L;
            ans.push_back('1');
        }
        else {
            ans.push_back('0');
        }
    }

    cout << ans << endl;
}
