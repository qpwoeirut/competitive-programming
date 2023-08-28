//1107g.cpp created at 01/23/21 20:31:54

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;

const int MN = 300005;

int N, K;
ll A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
        B[i] = K - B[i];
    }
    //for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << B[i] << ' '; } cerr << endl;

    map<ll,ll> mins;
    multiset<ll> cur;
    ll sum = 0;
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        //cerr << "i,A,B,sum: " << i << ' ' << A[i] << ' ' << B[i] << ' ' << sum << endl;
        //cerr << "cur: "; for (const int x: cur) { cerr << x << ' '; } cerr << endl;
        //cerr << "min: "; for (const auto x: mins) { cerr << '(' << x.fi << ' ' << x.se << ") "; } cerr << endl;

        if (cur.size() > 0) {
            ans = max(ans, sum + B[i] - *cur.begin());
        }
        //cerr << "ans: " << ans << endl;

        if (i+1 < N) {
            const ll gap = A[i+1] - A[i];
            ll mn = sum;
            while (mins.size() > 0 && mins.begin()->fi < gap) {
                const ll g = mins.begin()->fi;
                const ll val = mins.begin()->se;
                mn = min(mn, val);
                cur.erase(cur.find(val + (g * g)));
                mins.erase(mins.begin());
            }
            if (mins.size() > 0 && mins.begin()->fi == gap) {
                if (mins.begin()->se > mn) {
                    cur.erase(cur.find(mins.begin()->se + (mins.begin()->fi * mins.begin()->fi)));
                    mins.begin()->se = mn;
                    cur.insert(mins.begin()->se + (mins.begin()->fi * mins.begin()->fi));
                }
            } else {
                mins.insert(mins.begin(), make_pair(gap, mn));
                cur.insert(mn + (gap * gap));
            }
        }
        ans = max(ans, B[i]);
        sum += B[i];

    }

    cout << ans << endl;
}

