#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100005;
const int MOD = 1e9 + 7;

int N;
string S;

int get_val(const string& s, int i, const int finish) {
    int x = 0;
    for (; i<finish; ++i) x |= 1 << (s[i] - '0');
    return x;
}

const int PAIRS[12] = {
    (1 << 1) + (1 << 2),
    (1 << 2) + (1 << 3),
    (1 << 4) + (1 << 5),
    (1 << 5) + (1 << 6),
    (1 << 7) + (1 << 8),
    (1 << 8) + (1 << 9),
    
    (1 << 1) + (1 << 4),
    (1 << 4) + (1 << 7),
    (1 << 2) + (1 << 5),
    (1 << 5) + (1 << 8),
    (1 << 3) + (1 << 6),
    (1 << 6) + (1 << 9),
};

const int QUADS[4] = {
    PAIRS[0] + PAIRS[2],
    PAIRS[1] + PAIRS[3],
    PAIRS[2] + PAIRS[4],
    PAIRS[3] + PAIRS[5]
};

int is_pair(const string& s, const int i) {
    if (i+2 > N) return 0;
    const int val = get_val(s, i, i+2);
    for (int i=0; i<12; ++i) if (val == PAIRS[i]) return 1;
    return 0;
}
bool is_quad(const string& s, const int i) {
    if (i+4 > N) return false;
    const int val = get_val(s, i, i+4);
    return val == QUADS[0] || val == QUADS[1] || val == QUADS[2] || val == QUADS[3];
}
int quad_contrib(const int i) {
    if (!is_quad(S, i)) return 0;

    const int pairs = is_pair(S, i) | (is_pair(S, i + 1) << 1) | (is_pair(S, i + 2) << 2);
    const int exclude = i > 0 && S[i-1] == S[i+3] && (i == 1 || is_pair(S, i-2) == false);
    const int exclude2 = i > 1 && S[i-2] == S[i+3] && S[i-1] == S[i+2];
    if (pairs == 0b010) return 22 - exclude * 4 - exclude2;
    if (pairs == 0b101) return 20 - exclude * 4;
    if (pairs == 0b111) return 19 - exclude * 3;
    assert(false);
}

int A[MN];
ll dp[MN][100];

int solve() {
    for (int i=0; i<N; ++i) {
        A[i] = S[i] - '0';
    }
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<100; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    //cerr << "\n-----\n" << S << '\n';
    for (int i=0; i<N; ++i) {
        for (int j=0; j<100; ++j) {
            const int a = j / 10, b = j % 10;
            dp[i][j] %= MOD;
            dp[i+1][b * 10 + A[i]] += dp[i][j];
            if (is_pair(S, i)) {
                dp[i+2][A[i+1] * 10 + A[i]] += dp[i][j];
            }
            if (is_quad(S, i)) {
                dp[i+4][A[i+1] * 10 + A[i  ]] += dp[i][j] * 2;
                dp[i+4][A[i+2] * 10 + A[i  ]] += dp[i][j] * 2;
                dp[i+4][A[i+3] * 10 + A[i  ]] += dp[i][j] * 2;
                dp[i+4][A[i  ] * 10 + A[i+1]] += dp[i][j] * 2;
                dp[i+4][A[i+2] * 10 + A[i+1]] += dp[i][j] * 2;
                dp[i+4][A[i+3] * 10 + A[i+1]] += dp[i][j] * 2;
                dp[i+4][A[i  ] * 10 + A[i+2]] += dp[i][j] * 2;
                dp[i+4][A[i+1] * 10 + A[i+2]] += dp[i][j] * 2;
                dp[i+4][A[i+3] * 10 + A[i+2]] += dp[i][j] * (2 - is_pair(S, i+2) * (1 + is_pair(S, i)));

                if (b != A[i+3] || i == 0 || !is_quad(S, i-1)) {
                    dp[i+4][A[i  ] * 10 + A[i+3]] += dp[i][j] * 2;
                    dp[i+4][A[i+1] * 10 + A[i+3]] += dp[i][j] * (2 - is_pair(S, i+1));

                    bool exclude = (a == A[i+3] && b == A[i+2] && i >= 2 &&  is_quad(S, i - 2));
                    dp[i+4][A[i+2] * 10 + A[i+3]] += dp[i][j] * (1 - (is_pair(S, i) || exclude));
                }
            }
        }
    }

    ll ans = 0;
    for (int i=0; i<100; ++i) ans += dp[N][i];
    return ans % MOD;
}
// 63256325



bool ok_dp[MN];
bool possible(const string& T) {
    fill(ok_dp, ok_dp+N+1, false);
    ok_dp[0] = true;

    for (int i=0; i<N; ++i) {
        if (!ok_dp[i]) continue;
        if (S[i] == T[i]) ok_dp[i+1] = true;
        if (i+2 <= N && is_pair(T, i) && get_val(S, i, i+2) == get_val(T, i, i+2)) ok_dp[i+2] = true;
        if (i+4 <= N && is_quad(T, i) && get_val(S, i, i+4) == get_val(T, i, i+4)) ok_dp[i+4] = true;
    }

    return ok_dp[N];
}

int brute() {
    string T = S;
    sort(T.begin(), T.end());
    int ans = 0;
    do {
        if (possible(T)) {
            ++ans;
            //cerr << T << '\n';
        }
    } while (next_permutation(T.begin(), T.end()));
    return ans;
}

mt19937 rng(8);

void test() {
    for (N=8; N<=8; ++N) {
        cerr << N << endl;
        for (int t=0; t<1000000; ++t) {
            S = string(N, '!');
            for (int i=0; i<N; ++i) {
                S[i] = '1' + (rng() % 9);
            }
            const int sans = solve();
            const int bans = brute();
            if (sans != bans) {
                cerr << sans << ' ' << bans << endl;
                cerr << S << endl;
            }
            assert(sans == bans);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //test(); return 0;
    cin >> S; N = S.size(); cout << brute() << endl; cout << '\n' << solve() << endl; return 0;

    int T;
    cin >> T;

    while (T--) {
        cin >> S;
        N = S.size();
        cout << (N <= 8 ? brute() : solve()) << '\n';
    }
}

/*
63256325
*/
