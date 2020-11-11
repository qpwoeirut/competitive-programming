#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 16;

int N;
int VE, VC, CE, CC;
string s;

ll dp[MN][256][MN][MN];

bool type(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

ll solve(int idx, char prev, int equal, int similar) {
    if (type(prev) == true && (VE < equal || VC < similar)) return 0;
    if (type(prev) == false && (CE < equal || CC < similar)) return 0;
    if (idx == N) {
        return 1;
    }
    if (dp[idx][prev][equal][similar] != -1) {
        return dp[idx][prev][equal][similar];
    }

    dp[idx][prev][equal][similar] = 0;
    for (char nxt='a'; nxt<='z'; ++nxt) {
        if (s[idx] != '*' && s[idx] != nxt) continue;
        int new_equal = prev == nxt ? equal : 0;
        int new_similar = type(prev) == type(nxt) ? similar : 0;
        dp[idx][prev][equal][similar] += solve(idx+1, nxt, new_equal + 1, new_similar + 1);
    }

    return dp[idx][prev][equal][similar];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> VE >> VC >> CE >> CC;

    cin >> s;
    N = s.size();

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<256; ++j) {
            for (int k=0; k<MN; ++k) {
                for (int l=0; l<MN; ++l) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }

    ll ans = solve(0, 0, 0, 0);
    cout << ans << endl;
}
/*
1 1 1 1
a**


1 1 1 1
b*i


1 2 1 2
ancient

4 4 4 4
man****ipt


2 2 2 2
*boi*
*/
