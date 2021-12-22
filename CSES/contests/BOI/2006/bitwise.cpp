#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int MN = 102;

int N, P;
int K[MN];
vector<int> expr[MN];
int A[MN], B[MN];
int AA[MN], BB[MN];

int pick(const vector<int>& ex, const int bit) {
    pii best(-1, -1);
    for (const int x: ex) {
        if (A[x] + (1 << bit) <= B[x] || (A[x] & (1 << bit)) > 0 || (B[x] & (1 << bit)) > 0) {
            best = max(best, pii(A[x], x));
        }
    }
    return best.second;
}

int solve() {
    copy(AA, AA+N, A);
    copy(BB, BB+N, B);
    int ans = 0;
    for (int bit=30; bit>=0; --bit) {
        vector<int> chosen;
        for (int i=0; i<P; ++i) {
            chosen.push_back(pick(expr[i], bit));
        }
        if (count(chosen.begin(), chosen.end(), -1) == 0) {
            for (const int x: chosen) {
                if (A[x] + (1 << bit) <= B[x]) {
                    A[x] = 0;
                    B[x] = (1 << bit) - 1;
                } else if (B[x] - (A[x] & B[x]) )
            }
            ans += 1 << bit;
        }
    }
    return ans;
}

int val[MN];
int recurse(int i) {
    int res = 0;
    if (i == N) {
        for (int i=0; i<P; ++i) {
            int a = 0;
            for (const int x: expr[i]) {
                a |= val[x];
            }
            if (i == 0) res = a;
            else res &= a;
        }
        return res;
    }

    for (val[i]=A[i]; val[i]<=B[i]; ++val[i]) res = max(res, recurse(i+1));
    return res;
}

int brute() {
    copy(AA, AA+N, A);
    copy(BB, BB+N, B);
    return recurse(0);
}

void test() {
    for (N=1; N<=6; ++N) {
        for (P=1; P<=N; ++P) {
            cerr << N << ' ' << P << endl;
            for (int t=0; t<1000000; ++t) {
                fill(expr, expr+P, vector<int>());
                int exp_idx = 0;
                for (int i=0; i<N; ++i) {
                    expr[exp_idx].push_back(i);
                    if ((P - exp_idx == N - 1 - i || rand() % P == 0) && (exp_idx + 1 < P || i+1 == N)) {
                        K[exp_idx] = expr[exp_idx].size();
                        ++exp_idx;
                    }

                    AA[i] = rand() % 10;
                    BB[i] = AA[i] + (rand() % 10);
                }

                const int bans = brute();
                const int sans = solve();
                if (bans != sans) {
                    cout << N << ' ' << P << endl;
                    for (int i=0; i<P; ++i) {
                        cout << K[i] << ':';
                        for (int x: expr[i]) cout << ' ' << x;
                        cout << endl;
                    }
                    for (int i=0; i<N; ++i) {
                        cout << AA[i] << ' ' << BB[i] << '\n';
                    }
                    cout << bans << ' ' << sans << endl;
                }
                assert(bans == sans);
            }
        }
    }
}

int main() {
    //test(); return 0;
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> P;
    for (int i=0; i<P; ++i) {
        cin >> K[i];
    }
    int var = 0;
    for (int i=0; i<P; ++i) {
        for (int j=0; j<K[i]; ++j) {
            cin >> AA[var] >> BB[var];
            expr[i].push_back(var);
            ++var;
        }
    }
    
    //cout << solve() << '\n';
    cout << brute() << '\n';
}
/*
8 4
3 1 2 2
2 4
1 4
0 0
1 7
1 4
1 2
3 4
2 3
ans: 6

2 2
1 1
7 7
7 7
ans: 7

2 2
1 1
12 12
8 16
ans: 12

2 1
2
9 9
8 12
ans: 13
*/
