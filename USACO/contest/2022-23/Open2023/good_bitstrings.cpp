#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pll=pair<ll,ll>;

const ll INF = 2e18;

string gen_string(int64_t a, int64_t b) {
	string res;
	int ia = 0, ib = 0;
	while (ia + ib < a + b) {
		if ((__int128)ia * b <= (__int128)ib * a) {
			res += '0';
			ia++;
		} else {
			res += '1';
			ib++;
		}
	}
	return res;
}

ll A, B;
ll N;

int brute() {
    int ans = 0;
    const string s = gen_string(A, B);
    string prefix = string(1, s[0]);
    int a = s[0] == '0';
    for (int n=2; n<=N; ++n) {
        prefix += s[n-1];
        a += s[n-1] == '0';
        const int b = n - a;
        if (gen_string(a, b) == prefix) {
            ++ans;
            cerr << a << ' ' << b << ' ' << a/b << ' ' << (double)(a)/b << ' ' << double(A)/B << endl;
        }
    }
    return ans;
}

// compares frac * x and y (or frac and y/x)
int cmp_frac(const pll& frac, const __int128 x, const __int128 y) {
    if (frac.first * x < frac.second * y) return -1;
    else if (frac.first * x == frac.second * y) return 0;
    else return 1;
}

ll solve() {
    ll ans = 0;
	__int128 ia = 0, ib = 0;
    pll lb(0, 1), ub(INF, 1);
	while (ia + ib < A + B) {
		if (ia * B <= ib * A) {
            if (cmp_frac(lb, ib, ia) == -1) {
                lb = pll(ia, ib);
            }
			ia++;
		} else {
            if (cmp_frac(ub, ib, ia) == 1) {
                ub = pll(ia, ib);
            }
			ib++;
		}

        if (cmp_frac(lb, ib, ia) <= 0 && cmp_frac(ub, ib, ia) == 1) {
            ++ans;
        }
        //cerr << (ll)ia << ' ' << (ll)ib << " (" << lb.first << ',' << lb.second << ") (" <<  ub.first << ',' << ub.second << ")  " << ans << endl;
	}

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T --> 0) {
        cin >> A >> B;
        N = A + B;
        cout << solve() << '\n';
        //cout << brute() << '\n';
    }
}

